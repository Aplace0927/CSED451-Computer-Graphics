#ifndef MESH2D_HPP
#define MESH2D_HPP

#include <vector>
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace BBong {
struct Vertex2D {
public:
  glm::vec2 position;
  glm::vec3 color;
};

class Mesh2D {
private:
  std::vector<Vertex2D> vertices;
  std::vector<unsigned int> indices;

public:
  Mesh2D(const std::vector<Vertex2D> &vertices,
       const std::vector<unsigned int> &indices) {
    this->vertices = vertices;
    this->indices = indices;
  }
  ~Mesh2D() {}

  const std::vector<Vertex2D> getVectices() { return vertices; }

  void draw() {
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
};
} // namespace BBong

#endif // MESH2D