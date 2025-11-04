#ifndef OBJFILELOADER
#define OBJFILELOADER

#include <string>
#include <memory>
#include <vector>
#include <map>
#include <glm/glm.hpp>

#include "BBong/mesh3d.hpp"

namespace BBong {
class ObjFileLoader {
public:
  ObjFileLoader() = delete;
  static std::shared_ptr<Mesh3D> load(const std::string &path);

private:
  static unsigned int
  processVertex(const std::string &vertexData,
                const std::vector<glm::vec3> &temp_positions,
                const std::vector<glm::vec2> &temp_texCoords,
                const std::vector<glm::vec3> &temp_normals,
                std::vector<Vertex3D> &out_vertices,
                std::map<std::string, unsigned int> &vertexMap);
};
} // namespace BBong

#endif // OBJFILELOADER