#include "BBong/mesh3d.hpp"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <iostream>

#include "utility.hpp"

namespace BBong {
Mesh3D::Mesh3D(const std::vector<Vertex3D> &vertices,
               const std::vector<unsigned int> &indices)
    : m_vertices(vertices), m_indices(indices), VAO(std::nullopt), VBO(std::nullopt) {}

Mesh3D::~Mesh3D() {}

const std::vector<Vertex3D> Mesh3D::getVertices() { return m_vertices; }

void Mesh3D::draw(GraphicStyle style) {
  // if VAO and VBO are available, use retained mode rendering
  if (VAO.has_value()) {

    ShaderManager::getInstance().attachProgram();
    ShaderManager::getInstance().setUniformValue<glm::vec3>("uColor", defaultColor);
    ShaderStateDrawingMethod originalState = ShaderManager::getInstance().getCurrentDrawingState();
    
    switch (style) {
      case GraphicStyle::OPAQUE_POLYGON:
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDisable(GL_POLYGON_OFFSET_LINE);
        glEnable(GL_POLYGON_OFFSET_FILL);
        glPolygonOffset(1.0f, 1.0f); // Use a small offset

        glBindVertexArray(VAO.value());
        glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(m_indices.size()));
        glBindVertexArray(0);
        break;
      case GraphicStyle::WIREFRAME:
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDisable(GL_POLYGON_OFFSET_FILL);
        glEnable(GL_POLYGON_OFFSET_LINE);
        glPolygonOffset(1.0f, 1.0f);
        glLineWidth(0.3f);

        glBindVertexArray(VAO.value());
        glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(m_indices.size()));
        glBindVertexArray(0);
        break;
      case GraphicStyle::HIDDEN_LINE_REMOVAL:
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
        glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(m_indices.size()));
        glBindVertexArray(0);

        glDisable(GL_POLYGON_OFFSET_FILL); // Clean up offset

        // Visible Line Draw
        glDepthMask(GL_FALSE);
        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); 
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glLineWidth(0.3f);

        glBindVertexArray(VAO.value());
        glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(m_indices.size()));
        glBindVertexArray(0);

        break;
      case GraphicStyle::_GAME_BOUNDINGBOX:
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glEnable(GL_POLYGON_OFFSET_LINE);
        glPolygonOffset(1.0f, 1.0f);
        glLineWidth(0.5f);
        
        glBindVertexArray(VAO.value());
        glDrawArrays(GL_QUADS, 0, static_cast<GLsizei>(m_indices.size()));
        glBindVertexArray(0);
        break;
    }

    ShaderManager::getInstance().setCurrentDrawingState(originalState);
    ShaderManager::getInstance().detachProgram();
  }
}
} // namespace BBong