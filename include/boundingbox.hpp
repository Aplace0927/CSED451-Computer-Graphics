#ifndef BOUNDINGBOX_HPP
#define BOUNDINGBOX_HPP

#include <cstddef>
#include <stdexcept>
#include <array>
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace BoundingBox {
template <typename T> class BoundingBox {
public:
  // Default constructor
  BoundingBox() {
    throw std::runtime_error("Default constructor not implemented for this "
                             "BoundingBox specialization");
  }

  BoundingBox(T &_start, T &_end) : start(_start), end(_end) {}

  // Boundingbox itself cannot updated: only via Shape's applyTransition

  // Copy constructor
  BoundingBox(const BoundingBox<T> &other)
      : start(other.start), end(other.end) {}

  // Move constructor
  BoundingBox(BoundingBox<T> &&other) noexcept
      : start(std::move(other.start)), end(std::move(other.end)) {}

  // Copy assignment operator
  BoundingBox<T> &operator=(const BoundingBox<T> &other) {
    if (this != &other) {
      start = other.start;
      end = other.end;
    }
    return *this;
  }

  bool operator&&(const BoundingBox<T> &other) const {
    throw std::runtime_error("Collision detection operator not implemented for "
                             "this BoundingBox specialization");
  }
  
  BoundingBox<T> operator|(const BoundingBox<T> &other) const {
    throw std::runtime_error("Union operator not implemented for this "
                             "BoundingBox specialization");
  }

  void draw() {
    throw std::runtime_error(
        "draw() not implemented for this BoundingBox specialization");
  }

private:
  // Add bounding box state variables here
  T start;
  T end;
};

// Explicit specialization for BoundingBox<glm::vec3>

template <> inline BoundingBox<glm::vec3>::BoundingBox() {
  GLfloat max = std::numeric_limits<GLfloat>::max();
  GLfloat min = -std::numeric_limits<GLfloat>::max();
  start = glm::vec3(max, max, max);
  end = glm::vec3(min, min, min);
}

template <> inline
bool BoundingBox<glm::vec3>::operator&&(
  const BoundingBox<glm::vec3> &other
) const {
  if (start.x <= other.end.x && end.x >= other.start.x &&
      start.y <= other.end.y && end.y >= other.start.y) {
    return true; // Collision in all dimensions
  }
  return false; // No collision in any dimension
}

template <> inline
BoundingBox<glm::vec3> BoundingBox<glm::vec3>::operator|(
    const BoundingBox<glm::vec3> &other
) const {
  glm::vec3 newStart(std::min(start.x, other.start.x), std::min(start.y, other.start.y), 0.0f);
  glm::vec3 newEnd(std::max(end.x, other.end.x), std::max(end.y, other.end.y), 0.0f);
  return BoundingBox<glm::vec3>(newStart, newEnd);
}

template <> inline void BoundingBox<glm::vec3>::draw() {
  glBegin(GL_LINE_LOOP);
  glColor3f(1.0f, 0.0f, 0.0f); // Red color for bounding box
  glVertex3f(start[0], start[1], 0.0f);
  glVertex3f(end[0], start[1], 0.0f);
  glVertex3f(end[0], end[1], 0.0f);
  glVertex3f(start[0], end[1], 0.0f);
  glEnd();
}
} // namespace BoundingBox

#endif