#ifndef BOUNDINGBOX2D_HPP
#define BOUNDINGBOX2D_HPP

#include <glm/glm.hpp>

namespace Data {
class BoundingBox2D {
  glm::vec2 min;
  glm::vec2 max;

  BoundingBox2D()
      : min(std::numeric_limits<float>::max()),
        max(std::numeric_limits<float>::lowest()) {}

  BoundingBox2D(const glm::vec2 &minPoint, const glm::vec2 &maxPoint)
      : min(minPoint), max(maxPoint) {}

  bool Intersects(const BoundingBox2D &other) const {
    if (max.x < other.min.x || min.x > other.max.x) {
      return false;
    }
    if (max.y < other.min.y || min.y > other.max.y) {
      return false;
    }
    return true;
  }

  void Expand(const glm::vec2 &point) {
    min.x = std::min(min.x, point.x);
    min.y = std::min(min.y, point.y);
    max.x = std::max(max.x, point.x);
    max.y = std::max(max.y, point.y);
  }
};
} // namespace Data

#endif