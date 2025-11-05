#include "BBong/mesh2d.hpp"

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

namespace BBong {
Mesh2D::Mesh2D(const std::vector<Vertex2D> &vertices,
               const std::vector<unsigned int> &indices)
    : vertices(vertices), indices(indices) {}

Mesh2D::~Mesh2D() {}

const std::vector<Vertex2D> Mesh2D::getVectices() { return vertices; }

void Mesh2D::draw() {
  if (indices.empty())
    return;

  glBegin(GL_TRIANGLES);
  for (const unsigned int index : indices) {
    const Vertex2D &vertex = vertices[index];
    glColor3fv(glm::value_ptr(vertex.color));
    glVertex2fv(glm::value_ptr(vertex.position));
  }
  glEnd();
}
} // namespace BBong