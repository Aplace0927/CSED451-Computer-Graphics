#ifndef BOUNDINGBOX2D_HPP
#define BOUNDINGBOX2D_HPP

#include <glm/glm.hpp>
#include <limits>
#include <algorithm>
#include <vector>
#include <memory>

namespace BBong {
class BoundingBox2D {
private:
  glm::vec2 minOrigin;
  glm::vec2 maxOrigin;

  glm::vec2 minWorld;
  glm::vec2 maxWorld;

public:
  BoundingBox2D()
      : minOrigin(std::numeric_limits<float>::max()),
        maxOrigin(std::numeric_limits<float>::lowest()),
        minWorld(std::numeric_limits<float>::max()),
        maxWorld(std::numeric_limits<float>::lowest()) {}

  BoundingBox2D(const glm::vec2 &minPoint, const glm::vec2 &maxPoint)
      : minOrigin(minPoint), maxOrigin(maxPoint), minWorld(minPoint),
        maxWorld(maxPoint) {}

  BoundingBox2D(const BoundingBox2D &other) {
    minOrigin = other.minOrigin;
    maxOrigin = other.maxOrigin;
    minWorld = other.minWorld;
    maxWorld = other.maxWorld;
  }

  std::unique_ptr<BoundingBox2D> Clone() const {
    return std::make_unique<BoundingBox2D>(*this);
  }

  bool intersects(const BoundingBox2D &other) const {
    if (maxWorld.x < other.minWorld.x || minWorld.x > other.maxWorld.x) {
      return false;
    }
    if (maxWorld.y < other.minWorld.y || minWorld.y > other.maxWorld.y) {
      return false;
    }
    return true;
  }

  void expand(const glm::vec2 &point) {
    minOrigin.x = std::min(minOrigin.x, point.x);
    minOrigin.y = std::min(minOrigin.y, point.y);
    maxOrigin.x = std::max(maxOrigin.x, point.x);
    maxOrigin.y = std::max(maxOrigin.y, point.y);
  }

  void updateWorld(const glm::mat4 &matrix) {
    std::vector<glm::vec4> corners = {{minOrigin.x, minOrigin.y, 0.0f, 1.0f},
                                      {maxOrigin.x, minOrigin.y, 0.0f, 1.0f},
                                      {maxOrigin.x, maxOrigin.y, 0.0f, 1.0f},
                                      {minOrigin.x, maxOrigin.y, 0.0f, 1.0f}};

    minWorld = glm::vec2(std::numeric_limits<float>::max());
    maxWorld = glm::vec2(std::numeric_limits<float>::lowest());

    for (const auto &corner : corners) {
      glm::vec4 transformedCorner = matrix * corner;
      minWorld.x = std::min(minWorld.x, transformedCorner.x);
      minWorld.y = std::min(minWorld.y, transformedCorner.y);
      maxWorld.x = std::max(maxWorld.x, transformedCorner.x);
      maxWorld.y = std::max(maxWorld.y, transformedCorner.y);
    }
  }

  const glm::vec2 &getMinOrigin() const { return minOrigin; }
  const glm::vec2 &getMaxOrigin() const { return maxOrigin; }
  const glm::vec2 &getMinWorld() const { return minWorld; }
  const glm::vec2 &getMaxWorld() const { return maxWorld; }
};
} // namespace BBong

#endif // BOUNDINGBOX2D_HPP
