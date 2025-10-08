#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

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
  Transform *parent;
  std::vector<Transform *> children;
  glm::mat4 transformMatrix;
  bool isTransformChanged;

public:
  explicit Transform(GameObject::GameObject *owner)
      : Component(owner), position(0.0f),
        rotation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)), scale(1.0f),
        isTransformChanged(true), parent(nullptr) {}

  glm::mat4 GetModelMatrix() {
    if (isTransformChanged) {
      SetModelMatrix();
      isTransformChanged = false;
    }
    return transformMatrix;
  }

  void rotate(float angle_degrees, const glm::vec3 &axis) {
    rotation = glm::angleAxis(glm::radians(angle_degrees), axis) * rotation;
    rotation = glm::normalize(rotation);
    isTransformChanged = true;
  }

  void translate(const glm::vec3 &offset) {
    position += offset;
    isTransformChanged = true;
  }

  void applyScale(const glm::vec3 &factor) {
    scale *= factor;
    isTransformChanged = true;
  }

  void setRotation(glm::quat &rotation) {
    this->rotation = glm::normalize(rotation);
    isTransformChanged = true;
  }

  void setPosition(const glm::vec3 &position) {
    this->position = position;
    isTransformChanged = true;
  }

  void setScale(const glm::vec3 &scale) {
    this->scale = scale;
    isTransformChanged = true;
  }

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

  Transform *getParent() const { return parent; }

  void setParent(Transform *parent) {
    if (parent)
      this->parent = parent;
  }

private:
  void SetModelMatrix() {
    glm::mat4 translateMatrix = glm::translate(position);
    glm::mat4 rotationMatrix = glm::mat4_cast(rotation);
    glm::mat4 scaleMatrix = glm::scale(scale);
    transformMatrix = translateMatrix * rotationMatrix * scaleMatrix;
  }
};

Transform *createPlayer();
Transform *createEnemy();
// Transform *createBullet(Shape::RGBColor color);
} // namespace Component

#endif // TRANSFORM_HPP