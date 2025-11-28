#ifndef MESH3D_HPP
#define MESH3D_HPP

#include <vector>
#include <glm/glm.hpp>
#include <optional>

#include "BBong/shadermanager.hpp"

namespace BBong {
struct Vertex3D {
public:
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec2 texCoord;
};

struct VBOProps {
  GLuint vboVertices;
};

enum class GraphicStyle {
  OPAQUE_POLYGON,
  WIREFRAME,
  HIDDEN_LINE_REMOVAL,
  _GAME_BOUNDINGBOX
};

class Mesh3D {
private:
  std::vector<Vertex3D> m_vertices;
  std::vector<unsigned int> m_indices;

  std::optional<GLuint> VAO;
  std::optional<VBOProps> VBO;

public:
  Mesh3D(const std::vector<Vertex3D> &vertices,
         const std::vector<unsigned int> &indices);
  ~Mesh3D();

  const std::vector<Vertex3D> getVertices();
  glm::vec3 defaultColor = glm::vec3(1.0f, 1.0f, 1.0f);
  void draw(GraphicStyle style, GLuint textureID);

  void setVAO(GLuint vao) { VAO = vao; }
  void setVBO(const VBOProps &vbo) { VBO = vbo; }

  std::optional<GLuint> getVAO() const { return VAO; }
  std::optional<VBOProps> getVBO() const { return VBO; }
};
} // namespace BBong
#endif // MESH3D