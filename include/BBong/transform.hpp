#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <vector>
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>

#include "BBong/component.hpp"

namespace BBong {
class GameObject;

class Transform : public Component {
public:
  glm::vec3 position;
  glm::quat rotation;
  glm::vec3 scale;

private:
  Transform *parent;
  std::vector<Transform *> children;

  glm::mat4 localTransformMatrix;
  glm::mat4 worldTransformMatrix;

  bool isLocalDirty;
  bool isWorldDirty;

public:
  explicit Transform::Transform(GameObject *owner)
      : Component(owner), position(0.0f),
        rotation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)), scale(1.0f),
        parent(nullptr), localTransformMatrix(1.0f), worldTransformMatrix(1.0f),
        isLocalDirty(true), isWorldDirty(true) {};
  virtual std::unique_ptr<Component> clone(GameObject *newOwner) const override;

  glm::mat4 getWorldMatrix();
  glm::mat4 getLocalMatrix();

  void rotate(float angle_degrees, const glm::vec3 &axis);
  void translate(const glm::vec3 &offset);
  void applyScale(const glm::vec3 &factor);
  void setRotation(const glm::quat &newRotation);
  void setPosition(const glm::vec3 &position);
  void setScale(const glm::vec3 &scale);

  void addChild(Transform *child);
  void removeChild(Transform *child);

  std::vector<Transform *> getChildren() const;
  Transform *getNthChild(size_t n) const;
  Transform *getParent() const;
  void setParent(Transform *newParent);

private:
  glm::mat4 calculateLocalMatrix() const;
  void setLocalDirty();
  void setWorldDirty();
};
} // namespace BBong
#endif // TRANSFORM_HPP
