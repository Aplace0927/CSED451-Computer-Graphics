#ifndef MESH3D_HPP
#define MESH3D_HPP

#include <vector>
#include <glm/glm.hpp>

namespace BBong {
struct Vertex3D {
public:
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec2 texCoord;
};

enum class GraphicStyle {
  OPAQUE_POLYGON,
  WIREFRAME
};

class Mesh3D {
public:
  Mesh3D(const std::vector<Vertex3D> &vertices,
         const std::vector<unsigned int> &indices);
  ~Mesh3D();
  void draw(GraphicStyle style);

private:
  std::vector<Vertex3D> m_vertices;
  std::vector<unsigned int> m_indices;
};
} // namespace BBong
#endif // MESH3D