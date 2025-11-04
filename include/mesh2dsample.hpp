#ifndef MESHSAMPLE_HPP
#define MESHSAMPLE_HPP

#include <memory>
#include <vector>
#include <cmath>
#include "BBong/mesh2d.hpp"
#include "glm/glm.hpp"

namespace BBong {
inline std::shared_ptr<Mesh2D>
createHexagonMesh(float radius = 1.0f,
                  const glm::vec3 &centerColor = {1.0f, 1.0f, 1.0f},
                  const glm::vec3 &outerColor = {1.0f, 0.0f, 0.0f}) {

  std::vector<Vertex2D> vertices;
  std::vector<unsigned int> indices;

  vertices.push_back({{0.0f, 0.0f}, centerColor});

  const float M_PI = 3.14159265358979323846f;
  for (int i = 0; i < 6; ++i) {
    float angle = (M_PI / 3.0f) * i;
    vertices.push_back(
        {{radius * std::cos(angle), radius * std::sin(angle)}, outerColor});
  }

  indices.push_back(0);
  indices.push_back(1);
  indices.push_back(2);

  indices.push_back(0);
  indices.push_back(2);
  indices.push_back(3);

  indices.push_back(0);
  indices.push_back(3);
  indices.push_back(4);

  indices.push_back(0);
  indices.push_back(4);
  indices.push_back(5);

  indices.push_back(0);
  indices.push_back(5);
  indices.push_back(6);

  indices.push_back(0);
  indices.push_back(6);
  indices.push_back(1);

  return std::make_shared<Mesh2D>(vertices, indices);
}

inline std::shared_ptr<Mesh2D> createRainbowHexagonMesh(float radius = 1.0f) {

  std::vector<Vertex2D> vertices;
  std::vector<unsigned int> indices;

  // 중심 정점 (v0) - 흰색
  vertices.push_back({{0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}});

  // 바깥쪽 6개 정점 (v1 ~ v6) - 무지개색
  const float M_PI = 3.14159265358979323846f;
  std::vector<glm::vec3> colors = {
      {1.0f, 0.0f, 0.0f}, // Red (v1)
      {1.0f, 1.0f, 0.0f}, // Yellow (v2)
      {0.0f, 1.0f, 0.0f}, // Green (v3)
      {0.0f, 1.0f, 1.0f}, // Cyan (v4)
      {0.0f, 0.0f, 1.0f}, // Blue (v5)
      {1.0f, 0.0f, 1.0f}  // Magenta (v6)
  };

  for (int i = 0; i < 6; ++i) {
    float angle = (M_PI / 3.0f) * i;
    vertices.push_back({
        {radius * std::cos(angle), radius * std::sin(angle)}, // position
        colors[i]                                             // color
    });
  }

  // 인덱스는 위와 동일
  for (int i = 1; i <= 6; ++i) {
    indices.push_back(0);
    indices.push_back(i);
    indices.push_back((i % 6) + 1); // 다음 정점 (6 -> 1)
  }

  return std::make_shared<Mesh2D>(vertices, indices);
};
} // namespace BBong

#endif // MESHSAMPLE_HPP