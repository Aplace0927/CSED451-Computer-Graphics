#include "BBong/mesh3d.hpp"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <iostream>

namespace BBong {
Mesh3D::Mesh3D(const std::vector<Vertex3D> &vertices,
               const std::vector<unsigned int> &indices)
    : m_vertices(vertices), m_indices(indices) {}

Mesh3D::~Mesh3D() {}

const std::vector<Vertex3D> Mesh3D::getVertices() { return m_vertices; }

void Mesh3D::draw(GraphicStyle style) {
  switch (style) {
  case GraphicStyle::OPAQUE_POLYGON:
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    break;
  case GraphicStyle::WIREFRAME:
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    break;
  }

  glBegin(GL_TRIANGLES);

  for (unsigned int index : m_indices) {
    const Vertex3D &vertex = m_vertices[index];
    glNormal3f(vertex.normal.x, vertex.normal.y, vertex.normal.z);
    glTexCoord2f(vertex.texCoord.x, vertex.texCoord.y);
    glVertex3f(vertex.position.x, vertex.position.y, vertex.position.z);
  }

  glEnd();
}
} // namespace BBong