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

    // glEnable(GL_DEPTH_TEST);
    // glDisable(GL_POLYGON_OFFSET_LINE);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    // glDepthMask(GL_TRUE);

    // glBindVertexArray(VAO.value());
    // glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(m_indices.size()));
    // glBindVertexArray(0);

    ShaderManager::getInstance().attachProgram();
  
    ShaderManager::getInstance().setUniformValue<glm::vec3>("uColor", defaultColor);
  
    glBindVertexArray(VAO.value());
    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(m_indices.size()));
    glBindVertexArray(0);

    ShaderManager::getInstance().detachProgram();
  }
  else {
    switch (style) {
      case GraphicStyle::OPAQUE_POLYGON:
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glBegin(GL_TRIANGLES);
        break;
      case GraphicStyle::WIREFRAME:
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glBegin(GL_TRIANGLES);
        break;
      case GraphicStyle::_GAME_BOUNDINGBOX:
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glBegin(GL_QUADS);
        break;
    }
   for (unsigned int index : m_indices) {
      const Vertex3D &vertex = m_vertices[index];
      glNormal3f(vertex.normal.x, vertex.normal.y, vertex.normal.z);
      glTexCoord2f(vertex.texCoord.x, vertex.texCoord.y);
      glColor3f(defaultColor.r, defaultColor.g, defaultColor.b);      
      glVertex3f(vertex.position.x, vertex.position.y, vertex.position.z);
    }
  glEnd(); 
  }
}
} // namespace BBong