#ifndef BOUNDINGBOX3D_HPP // 파일명과 일치시키는 것을 권장합니다.
#define BOUNDINGBOX3D_HPP

#include <glm/glm.hpp>
#include <limits>
#include <algorithm>
#include <vector>
#include <memory>

namespace BBong {
class BoundingBox3D {
private:
  glm::vec3 minOrigin;
  glm::vec3 maxOrigin;

  glm::vec3 minWorld;
  glm::vec3 maxWorld;

public:
  BoundingBox3D()
      : minOrigin(std::numeric_limits<float>::max()),
        maxOrigin(std::numeric_limits<float>::lowest()),
        minWorld(std::numeric_limits<float>::max()),
        maxWorld(std::numeric_limits<float>::lowest()) {}

  BoundingBox3D(const glm::vec3 &minPoint, const glm::vec3 &maxPoint)
      : minOrigin(minPoint), maxOrigin(maxPoint), minWorld(minPoint),
        maxWorld(maxPoint) {}

  BoundingBox3D(const BoundingBox3D &other) {
    minOrigin = other.minOrigin;
    maxOrigin = other.maxOrigin;
    minWorld = other.minWorld;
    maxWorld = other.maxWorld;
  }

  std::unique_ptr<BoundingBox3D> Clone() const {
    return std::make_unique<BoundingBox3D>(*this);
  }

  bool intersects(const BoundingBox3D &other) const {
    if (maxWorld.x < other.minWorld.x || minWorld.x > other.maxWorld.x) {
      return false;
    }
    if (maxWorld.y < other.minWorld.y || minWorld.y > other.maxWorld.y) {
      return false;
    }
    if (maxWorld.z < other.minWorld.z || minWorld.z > other.maxWorld.z) {
      return false;
    }
    return true;
  }

  void expand(const glm::vec3 &point) {
    minOrigin.x = std::min(minOrigin.x, point.x);
    minOrigin.y = std::min(minOrigin.y, point.y);
    minOrigin.z = std::min(minOrigin.z, point.z);
    maxOrigin.x = std::max(maxOrigin.x, point.x);
    maxOrigin.y = std::max(maxOrigin.y, point.y);
    maxOrigin.z = std::max(maxOrigin.z, point.z);
  }

  void updateWorld(const glm::mat4 &matrix) {
    std::vector<glm::vec4> corners = {
        {minOrigin.x, minOrigin.y, minOrigin.z, 1.0f},
        {maxOrigin.x, minOrigin.y, minOrigin.z, 1.0f},
        {maxOrigin.x, maxOrigin.y, minOrigin.z, 1.0f},
        {minOrigin.x, maxOrigin.y, minOrigin.z, 1.0f},
        {minOrigin.x, minOrigin.y, maxOrigin.z, 1.0f},
        {maxOrigin.x, minOrigin.y, maxOrigin.z, 1.0f},
        {maxOrigin.x, maxOrigin.y, maxOrigin.z, 1.0f},
        {minOrigin.x, maxOrigin.y, maxOrigin.z, 1.0f}};

    minWorld = glm::vec3(std::numeric_limits<float>::max());
    maxWorld = glm::vec3(std::numeric_limits<float>::lowest());

    for (const auto &corner : corners) {
      glm::vec4 transformedCorner = matrix * corner;

      minWorld.x = std::min(minWorld.x, transformedCorner.x);
      minWorld.y = std::min(minWorld.y, transformedCorner.y);
      minWorld.z = std::min(minWorld.z, transformedCorner.z);
      maxWorld.x = std::max(maxWorld.x, transformedCorner.x);
      maxWorld.y = std::max(maxWorld.y, transformedCorner.y);
      maxWorld.z = std::max(maxWorld.z, transformedCorner.z);
    }
  }

  const glm::vec3 &getMinOrigin() const { return minOrigin; }
  const glm::vec3 &getMaxOrigin() const { return maxOrigin; }
  const glm::vec3 &getMinWorld() const { return minWorld; }
  const glm::vec3 &getMaxWorld() const { return maxWorld; }
};
} // namespace BBong

#endif // BOUNDINGBOX3D_HPP