#ifndef OBJLOADER_HPP
#define OBJLOADER_HPP

#include <string>
#include <memory>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>

#include "BBong/mesh3d.hpp"

namespace BBong {
class ObjLoader {
public:
  ObjLoader() = delete;
  static std::shared_ptr<Mesh3D> load(const std::string &path);
  static std::shared_ptr<Mesh3D> loadFromVertex3D(
    const std::vector<Vertex3D> &vertices,
    const std::vector<unsigned int> &indices
  );
  static std::shared_ptr<Mesh3D> loadtoGPU(const std::vector<Vertex3D> &vertices, const std::vector<unsigned int> &indices);
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

#endif // OBJLOADER_HPP