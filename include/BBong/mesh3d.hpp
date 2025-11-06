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
  WIREFRAME,
  _GAME_BOUNDINGBOX
};

class Mesh3D {
private:
  std::vector<Vertex3D> m_vertices;
  std::vector<unsigned int> m_indices;
public:
  Mesh3D(const std::vector<Vertex3D> &vertices,
         const std::vector<unsigned int> &indices);
  ~Mesh3D();
  const std::vector<Vertex3D> getVertices();
  void draw(GraphicStyle style);
};
} // namespace BBong
#endif // MESH3D