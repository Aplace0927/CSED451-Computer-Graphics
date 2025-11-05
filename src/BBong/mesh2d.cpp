#include "BBong/mesh2d.hpp"

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

namespace BBong {
Mesh2D::Mesh2D(const std::vector<Vertex2D> &vertices,
               const std::vector<unsigned int> &indices)
    : m_vertices(vertices), m_indices(indices) {}

Mesh2D::~Mesh2D() {}

void Mesh2D::draw() {
  if (m_indices.empty())
    return;

  glBegin(GL_TRIANGLES);
  for (const unsigned int index : m_indices) {
    const Vertex2D &vertex = m_vertices[index];
    glColor3fv(glm::value_ptr(vertex.color));
    glVertex2fv(glm::value_ptr(vertex.position));
  }
  glEnd();
}
} // namespace BBong