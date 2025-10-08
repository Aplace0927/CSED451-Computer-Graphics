#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace Data {
struct Vertex2D {
  glm::vec2 position;
  glm::vec3 color;
};

class Mesh2D {
private:
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;

public:
  Mesh(const std::vector<Vertex> &vertices,
       const std::vector<unsigned int> &indices) {
    this->vertices = vertices;
    this->indices = indices;
  }
  ~Mesh() {}

  void draw() {
    if (indices.empty())
      return;

    glBegin(GL_TRIANGLES);

    for (const unsigned int index : indices) {
      const Vertex &vertex = vertices[index];
      glColor3fv(glm::value_ptr(vertex.color));
      glVertex2fv(glm::value_ptr(vertex.position));
    }

    glEnd();
  }
};
} // namespace Data

#endif // MESH_HPP