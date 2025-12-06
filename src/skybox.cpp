#include "skybox.hpp"
#include <vector>
#include <iostream>
#include <cstdlib>
#include "stb/stb_image.h"
#include <glm/gtc/matrix_transform.hpp>

#include "BBong/camera.hpp"

namespace BBong {

static unsigned char *resizeFaceData(const unsigned char *src, int srcW,
                                     int srcH, int channels, int targetW,
                                     int targetH) {
  size_t dataSize = targetW * targetH * channels;
  unsigned char *resized = (unsigned char *)malloc(dataSize);
  if (!resized)
    return nullptr;

  for (int y = 0; y < targetH; ++y) {
    for (int x = 0; x < targetW; ++x) {
      int srcX = x * srcW / targetW;
      int srcY = y * srcH / targetH;

      int srcIdx = (srcY * srcW + srcX) * channels;
      int dstIdx = (y * targetW + x) * channels;

      for (int c = 0; c < channels; ++c) {
        resized[dstIdx + c] = src[srcIdx + c];
      }
    }
  }
  return resized;
}

std::vector<float> skyboxVertices = {
    // Coordinates
    -1.0f, -1.0f, 1.0f,  // 0
    1.0f,  -1.0f, 1.0f,  // 1
    1.0f,  -1.0f, -1.0f, // 2
    -1.0f, -1.0f, -1.0f, // 3
    -1.0f, 1.0f,  1.0f,  // 4
    1.0f,  1.0f,  1.0f,  // 5
    1.0f,  1.0f,  -1.0f, // 6
    -1.0f, 1.0f,  -1.0f  // 7
};

std::vector<unsigned int> skyboxIndices = {
    // Right
    1, 2, 6, 6, 5, 1,
    // Left
    0, 4, 7, 7, 3, 0,
    // Top
    4, 5, 6, 6, 7, 4,
    // Bottom
    0, 3, 2, 2, 1, 0,
    // Back
    0, 1, 5, 5, 4, 0,
    // Front
    3, 7, 6, 6, 2, 3};

Skybox::Skybox(GameObject *owner) : ClonableComponent(owner) { initGeometry(); }

Skybox::Skybox(const Skybox &other) : ClonableComponent(nullptr) {
  // Geometry is local GPU state; re-init
  initGeometry();
  shaderAlias = other.shaderAlias;
  facePaths = other.facePaths;
  if (!facePaths[0].empty()) {
    cubemapTex = loadCubemap(facePaths);
  }
}

Skybox::~Skybox() { destroyGeometry(); }

void Skybox::setCubemapFaces(const std::array<std::string, 6> &faces) {
  facePaths = faces;
  if (cubemapTex) {
    glDeleteTextures(1, &cubemapTex);
    cubemapTex = 0;
  }
  cubemapTex = loadCubemap(facePaths);
}

void Skybox::initGeometry() {
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);

  glBindVertexArray(vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER,
               static_cast<GLsizeiptr>(skyboxVertices.size() * sizeof(float)),
               skyboxVertices.data(), GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(
      GL_ELEMENT_ARRAY_BUFFER,
      static_cast<GLsizeiptr>(skyboxIndices.size() * sizeof(unsigned int)),
      skyboxIndices.data(), GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Skybox::destroyGeometry() {
  if (cubemapTex) {
    glDeleteTextures(1, &cubemapTex);
    cubemapTex = 0;
  }
  if (ebo) {
    glDeleteBuffers(1, &ebo);
    ebo = 0;
  }
  if (vbo) {
    glDeleteBuffers(1, &vbo);
    vbo = 0;
  }
  if (vao) {
    glDeleteVertexArrays(1, &vao);
    vao = 0;
  }
}

GLuint Skybox::loadCubemap(const std::array<std::string, 6> &faces) {
  GLuint texID;
  glGenTextures(1, &texID);
  glBindTexture(GL_TEXTURE_CUBE_MAP, texID);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

  stbi_set_flip_vertically_on_load(0);

  int baseW = 0, baseH = 0, baseC = 0;

  for (unsigned int i = 0; i < 6; ++i) {
    int w, h, fileCh;
    // Force channels to match the first loaded face (baseC)
    // if i==0, desired=0 (auto). if i>0, desired=baseC.
    int desiredCh = (i == 0) ? 0 : baseC;

    unsigned char *data =
        stbi_load(faces[i].c_str(), &w, &h, &fileCh, desiredCh);

    if (data) {
      // Determine the actual channels in the buffer
      int bufferCh = (desiredCh == 0) ? fileCh : desiredCh;

      // Set base dimensions from the first face
      if (i == 0) {
        baseW = w;
        baseH = h;
        baseC = bufferCh;
      }

      unsigned char *uploadData = data;
      bool didResize = false;

      // Check if current face size mismatches the base size
      if (w != baseW || h != baseH) {
        std::cerr << "[Skybox] Warning: Face " << i << " size (" << w << "x"
                  << h << ") differs from base (" << baseW << "x" << baseH
                  << "). Resizing..." << std::endl;

        uploadData = resizeFaceData(data, w, h, bufferCh, baseW, baseH);
        if (uploadData) {
          didResize = true;
        } else {
          // Fallback to original if malloc failed (shouldn't happen often)
          uploadData = data;
          std::cerr << "[Skybox] Error: Failed to resize face " << i
                    << std::endl;
        }
      }

      GLenum format =
          bufferCh == 4
              ? GL_RGBA
              : (bufferCh == 3 ? GL_RGB : (bufferCh == 1 ? GL_RED : GL_RGB));

      glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format,
                   baseW, // Use base dimensions
                   baseH, 0, format, GL_UNSIGNED_BYTE, uploadData);

      // Clean up
      if (didResize) {
        free(uploadData); // Free the resized buffer
      }
      stbi_image_free(data); // Free the original stbi buffer

    } else {
      std::cerr << "Failed to load cubemap face: " << faces[i] << std::endl;
      stbi_image_free(data);
    }
  }

  // Restore default alignment
  glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
  stbi_set_flip_vertically_on_load(1);
  return texID;
}

void Skybox::renderUpdate() {
  if (!cubemapTex)
    return;

  Camera *cam = GraphicsManager::getInstance().getMainCamera();
  if (!cam)
    return;

  glDepthFunc(GL_LEQUAL);

  ShaderStateDrawingMethod originalState =
      ShaderManager::getInstance().getCurrentDrawingState();
  ShaderManager::getInstance().attachProgram(shaderAlias);

  glm::mat4 view = glm::mat4(glm::mat3(cam->getViewMatrix()));
  glm::mat4 proj = cam->getProjectionMatrix();

  ShaderManager::getInstance().setUniformValue(shaderAlias, "view", view);
  ShaderManager::getInstance().setUniformValue(shaderAlias, "projection", proj);

  glBindVertexArray(vao);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTex);

  glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(skyboxIndices.size()),
                 GL_UNSIGNED_INT, (void *)0);

  glBindVertexArray(0);

  ShaderManager::getInstance().setCurrentDrawingState(originalState);
  glDepthFunc(GL_LESS);
  ShaderManager::getInstance().detachProgram();
}

} // namespace BBong