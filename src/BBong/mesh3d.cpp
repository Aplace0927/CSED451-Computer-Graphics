#include "BBong/mesh3d.hpp"

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace BBong {
Mesh3D::Mesh3D(const std::vector<Vertex3D> &vertices,
               const std::vector<unsigned int> &indices)
    : m_vertices(vertices), m_indices(indices), VAO(std::nullopt),
      VBO(std::nullopt) {

  if (m_vertices.empty() || m_indices.empty()) {
    return;
  }

  calculateTangents();

  GLuint vaoID, vboID, eboID;

  glGenVertexArrays(1, &vaoID);
  glGenBuffers(1, &vboID);
  glGenBuffers(1, &eboID);

  glBindVertexArray(vaoID);

  glBindBuffer(GL_ARRAY_BUFFER, vboID);
  glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex3D),
               m_vertices.data(), GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int),
               m_indices.data(), GL_STATIC_DRAW);

  // 0: Position
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D),
                        (void *)offsetof(Vertex3D, position));
  // 1: Normal
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D),
                        (void *)offsetof(Vertex3D, normal));
  // 2: TexCoord
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3D),
                        (void *)offsetof(Vertex3D, texCoord));
  // 3: Tangent (New)
  glEnableVertexAttribArray(3);
  glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D),
                        (void *)offsetof(Vertex3D, tangent));

  glBindVertexArray(0);

  this->VAO = vaoID;

  VBOProps props;
  props.vboVertices = vboID;
  this->VBO = props;
}
Mesh3D::~Mesh3D() {
  if (VBO.has_value()) {
    glDeleteBuffers(1, &VBO.value().vboVertices);
  }
  if (VAO.has_value()) {
    GLuint vaoID = VAO.value();
    glDeleteVertexArrays(1, &vaoID);
  }
}

void Mesh3D::calculateTangents() {
  for (auto &v : m_vertices) {
    v.tangent = glm::vec3(0.0f);
  }

  for (size_t i = 0; i < m_indices.size(); i += 3) {
    Vertex3D &v0 = m_vertices[m_indices[i]];
    Vertex3D &v1 = m_vertices[m_indices[i + 1]];
    Vertex3D &v2 = m_vertices[m_indices[i + 2]];

    glm::vec3 edge1 = v1.position - v0.position;
    glm::vec3 edge2 = v2.position - v0.position;

    glm::vec2 deltaUV1 = v1.texCoord - v0.texCoord;
    glm::vec2 deltaUV2 = v2.texCoord - v0.texCoord;

    float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
    if (std::isinf(f) || std::isnan(f))
      f = 0.0f;

    glm::vec3 tangent;
    tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
    tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
    tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

    v0.tangent += tangent;
    v1.tangent += tangent;
    v2.tangent += tangent;
  }

  for (auto &v : m_vertices) {
    if (glm::length(v.tangent) > 0.0f)
      v.tangent = glm::normalize(v.tangent);
  }
}

const std::vector<Vertex3D> Mesh3D::getVertices() { return m_vertices; }

void Mesh3D::draw(GraphicStyle style, GLuint textureID, GLuint normalMapID) {
  if (VAO.has_value()) {

    ShaderManager::getInstance().attachProgram();

    // Texture Unit 0: Diffuse
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    ShaderManager::getInstance().setUniformValue<int>("samp2DTexture", 0);
    ShaderManager::getInstance().setUniformValue<float>(
        "uFloatUseTexture", textureID ? 1.0f : 0.0f);

    // Texture Unit 1: Normal Map
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, normalMapID);
    ShaderManager::getInstance().setUniformValue<int>("normalMap", 1);
    ShaderManager::getInstance().setUniformValue<float>(
        "uFloatUseNormalMap", normalMapID ? 1.0f : 0.0f);

    ShaderManager::getInstance().setUniformValue<glm::vec3>("uColor",
                                                            defaultColor);
    ShaderStateDrawingMethod originalState =
        ShaderManager::getInstance().getCurrentDrawingState();

    switch (style) {
    case GraphicStyle::OPAQUE_POLYGON:
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      glDisable(GL_POLYGON_OFFSET_LINE);
      glEnable(GL_POLYGON_OFFSET_FILL);
      glPolygonOffset(1.0f, 1.0f);

      glBindVertexArray(VAO.value());
      glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indices.size()),
                     GL_UNSIGNED_INT, 0);
      glBindVertexArray(0);
      break;

    case GraphicStyle::WIREFRAME:
      ShaderManager::getInstance().setUniformValue<float>("uFloatUseTexture", 0.0f);
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      glDisable(GL_POLYGON_OFFSET_FILL);
      glEnable(GL_POLYGON_OFFSET_LINE);
      glPolygonOffset(1.0f, 1.0f);
      glLineWidth(0.3f);

      glBindVertexArray(VAO.value());
      glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indices.size()),
                     GL_UNSIGNED_INT, 0);
      glBindVertexArray(0);
      break;

    case GraphicStyle::HIDDEN_LINE_REMOVAL:
      ShaderManager::getInstance().setUniformValue<float>("uFloatUseTexture", 0.0f);
      glEnable(GL_DEPTH_TEST);
      glDepthFunc(GL_LESS);

      // 1. Enable offset for the FILL to slightly push it away from the lines
      glEnable(GL_POLYGON_OFFSET_FILL);
      glPolygonOffset(1.0f, 1.0f);

      // 2. Set mode to FILL, and crucially, block color writes
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
      glDepthMask(GL_TRUE);

      // Draw the geometry (establishes depth)
      glBindVertexArray(VAO.value());
      glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indices.size()),
                     GL_UNSIGNED_INT, 0);
      glBindVertexArray(0);

      glDisable(GL_POLYGON_OFFSET_FILL);

      // Visible Line Draw
      glDepthMask(GL_FALSE);
      glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      glLineWidth(0.3f);

      glBindVertexArray(VAO.value());
      glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indices.size()),
                     GL_UNSIGNED_INT, 0);
      glBindVertexArray(0);
      break;

    case GraphicStyle::_GAME_BOUNDINGBOX:
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      glEnable(GL_POLYGON_OFFSET_LINE);
      glPolygonOffset(1.0f, 1.0f);
      glLineWidth(0.5f);

      glBindVertexArray(VAO.value());
      glDrawElements(GL_QUADS, static_cast<GLsizei>(m_indices.size()),
                     GL_UNSIGNED_INT, 0);
      glBindVertexArray(0);
      break;
    }

    glActiveTexture(GL_TEXTURE0);

    ShaderManager::getInstance().setCurrentDrawingState(originalState);
    ShaderManager::getInstance().detachProgram();
  }
}
} // namespace BBong