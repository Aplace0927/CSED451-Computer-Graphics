#include "skybox.hpp"
#include <vector>
#include "stb/stb_image.h"

#include "BBong/camera.hpp"

namespace BBong {

std::vector<float> skyboxVertices =
{
	//   Coordinates
	-1.0f, -1.0f,  1.0f,//        7--------6
	 1.0f, -1.0f,  1.0f,//       /|       /|
	 1.0f, -1.0f, -1.0f,//      4--------5 |
	-1.0f, -1.0f, -1.0f,//      | |      | |
	-1.0f,  1.0f,  1.0f,//      | 3------|-2
	 1.0f,  1.0f,  1.0f,//      |/       |/
	 1.0f,  1.0f, -1.0f,//      0--------1
	-1.0f,  1.0f, -1.0f
};

std::vector<unsigned int> skyboxIndices =
{
	// Right
	1, 2, 6,
	6, 5, 1,
	// Left
	0, 4, 7,
	7, 3, 0,
	// Top
	4, 5, 6,
	6, 7, 4,
	// Bottom
	0, 3, 2,
	2, 1, 0,
	// Back
	0, 1, 5,
	5, 4, 0,
	// Front
	3, 7, 6,
	6, 2, 3
};
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
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(skyboxVertices.size() * sizeof(float)), skyboxVertices.data(), GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glBindVertexArray(0);
}

void Skybox::destroyGeometry() {
  if (cubemapTex) { glDeleteTextures(1, &cubemapTex); cubemapTex = 0; }
  if (vbo) { glDeleteBuffers(1, &vbo); vbo = 0; }
  if (vao) { glDeleteVertexArrays(1, &vao); vao = 0; }
}

GLuint Skybox::loadCubemap(const std::array<std::string, 6> &faces) {
  GLuint texID;
  glGenTextures(1, &texID);
  glBindTexture(GL_TEXTURE_CUBE_MAP, texID);

  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

  bool anyLoaded = false;

  for (unsigned int i = 0; i < 6; ++i) {
    int w, h, ch;
    unsigned char *data = stbi_load(faces[i].c_str(), &w, &h, &ch, 0);
    if (data) {
      GLenum format = ch == 4 ? GL_RGBA : (ch == 3 ? GL_RGB : (ch == 1 ? GL_RED : GL_RGB));
      glTexImage2D(
        GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
        0,
        format,
        w,
        h,
        0,
        format,
        GL_UNSIGNED_BYTE,
        data
        );
      stbi_image_free(data);
      std::cerr << "Loaded cubemap face: " << faces[i] << std::endl;
    }
  }

  // Generate mipmaps for smoother sampling
  glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

  // Restore TextureManager default (flipped load for 2D textures)
  stbi_set_flip_vertically_on_load(1);
  return texID;
}

void Skybox::renderUpdate() {
  if (!cubemapTex) return; // wait until faces set

  Camera *cam = GraphicsManager::getInstance().getMainCamera();
  if (!cam) return;

  // Save current GL state and use skybox shader
  glDepthFunc(GL_LEQUAL);

  ShaderStateDrawingMethod originalState = ShaderManager::getInstance().getCurrentDrawingState();
  ShaderManager::getInstance().attachProgram(shaderAlias);

  // Remove translation from view matrix
  glm::mat4 view = cam->getViewMatrix();
  view = glm::mat4(glm::mat3(view));
  glm::mat4 proj = cam->getProjectionMatrix();

  ShaderManager::getInstance().setUniformValue(shaderAlias, "view", view);
  ShaderManager::getInstance().setUniformValue(shaderAlias, "projection", proj);

  // Render state: draw last, depth func LEQUAL, avoid writing depth


  glBindVertexArray(vao);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTex);
  glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(skyboxIndices.size()), GL_UNSIGNED_INT, skyboxIndices.data());
  glBindVertexArray(0);

  // Restore GL state
  ShaderManager::getInstance().setCurrentDrawingState(originalState);
  glDepthFunc(GL_LESS);
  ShaderManager::getInstance().detachProgram();
}

} // namespace BBong
