#ifndef MESH2D_HPP
#define MESH2D_HPP

#include <vector>
#include <glm/glm.hpp>

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
         const std::vector<unsigned int> &indices);
  ~Mesh2D();

  const std::vector<Vertex2D> getVectices();
  void draw();
};
} // namespace BBong
#endif // MESH2D_HPP