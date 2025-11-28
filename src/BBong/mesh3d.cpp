#include "BBong/mesh3d.hpp"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <iostream>

#include "utility.hpp"

namespace BBong {
Mesh3D::Mesh3D(const std::vector<Vertex3D> &vertices,
               const std::vector<unsigned int> &indices)
    : m_vertices(vertices), m_indices(indices), VAO(std::nullopt),
      VBO(std::nullopt) {

  if (m_vertices.empty() || m_indices.empty()) {
    return;
  }

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

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D),
                        (void *)offsetof(Vertex3D, position));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D),
                        (void *)offsetof(Vertex3D, normal));
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3D),
                        (void *)offsetof(Vertex3D, texCoord));

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

const std::vector<Vertex3D> Mesh3D::getVertices() { return m_vertices; }

void Mesh3D::draw(GraphicStyle style, unsigned int textureID) {
  // if VAO and VBO are available, use retained mode rendering
  if (VAO.has_value()) {

    ShaderManager::getInstance().attachProgram();
    ShaderManager::getInstance().setUniformValue<float>("uFloatUseTexture", textureID ? 1.0f : 0.0f);
    ShaderManager::getInstance().setUniformValue<glm::vec3>("uColor",
                                                            defaultColor);
    ShaderStateDrawingMethod originalState =
        ShaderManager::getInstance().getCurrentDrawingState();

    switch (style) {
    case GraphicStyle::OPAQUE_POLYGON:
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      glDisable(GL_POLYGON_OFFSET_LINE);
      glEnable(GL_POLYGON_OFFSET_FILL);
      glPolygonOffset(1.0f, 1.0f); // Use a small offset
      glBindTexture(GL_TEXTURE_2D, textureID);
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
      glDepthFunc(GL_LESS); // Standard depth function

      // 1. Enable offset for the FILL to slightly push it away from the lines
      glEnable(GL_POLYGON_OFFSET_FILL);
      glPolygonOffset(1.0f, 1.0f); // Use a small offset

      // 2. Set mode to FILL, and crucially, block color writes
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE); // BLOCK color writes
      glDepthMask(GL_TRUE); // ENABLE depth writes (THIS IS THE PRIMARY GOAL)

      // Draw the geometry (establishes depth)
      glBindVertexArray(VAO.value());
      glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indices.size()),
                     GL_UNSIGNED_INT, 0);
      glBindVertexArray(0);

      glDisable(GL_POLYGON_OFFSET_FILL); // Clean up offset

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

    ShaderManager::getInstance().setCurrentDrawingState(originalState);
    ShaderManager::getInstance().detachProgram();
  }
}
} // namespace BBong