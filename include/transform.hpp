#ifndef SCENEGRAPH_HPP
#define SCENEGRAPH_HPP

#include <vector>
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <GL/glew.h>

#include "utility.hpp"
#include "shape.hpp"
#include "component.hpp"

namespace Component {
class Transform : public Component {
public:
  glm::vec3 position;
  glm::quat rotation;
  glm::vec3 scale;

private:
  std::vector<Transform *> children;
  Transform *parent;
  glm::mat4 transformMatrix;
  bool isTransformChanged;

public:
  Transform()
      : position(0.0f), rotation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)),
        scale(1.0f), parent(nullptr), isTransformChanged(false) {
    SetModelMatrix();
  }

  glm::mat4 GetModelMatrix() {
    if (isTransformChanged)
      SetModelMatrix();
    return transformMatrix;
  }

  void rotate(float angle_degrees, const glm::vec3 &axis) {
    rotation = glm::angleAxis(glm::radians(angle_degrees), axis) * rotation;
    rotation = glm::normalize(rotation);
  }

  void translate(const glm::vec3 &offset) { position += offset; }

  void addChild(Transform *child) { children.push_back(child); }
  void removeChild(Transform *child) {
    children.erase(std::remove(children.begin(), children.end(), child),
                   children.end());
  }
  Transform *getNthChild(size_t n) const {
    if (n < children.size()) {
      return children[n];
    }
    return nullptr;
  }

private:
  void SetModelMatrix() {
    glm::mat4 scaleMatrix = glm::scale(scale);
    glm::mat4 rotationMatrix = glm::mat4_cast(rotation);
    glm::mat4 translateMatrix = glm::translate(position);
    transformMatrix = translateMatrix * rotationMatrix * scaleMatrix;
  }
};

Transform *createPlayer();
Transform *createEnemy();
Transform *createBullet(Shape::RGBColor color);
} // namespace Transform

#endif // SCENEGRAPH_HPP