#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <vector>
#include <algorithm>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>

#include "BBong/component.hpp"

namespace BBong {
class GameObject;

class Transform : public Component {
public:
  explicit Transform(GameObject *owner)
      : Component(owner), position(0.0f),
        rotation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)), scale(1.0f),
        parent(nullptr), localTransformMatrix(1.0f), worldTransformMatrix(1.0f),
        isLocalDirty(true), isWorldDirty(true) {};

  virtual std::unique_ptr<Component> clone(GameObject *newOwner) const override;

  glm::mat4 getWorldMatrix() const;
  glm::mat4 getLocalMatrix() const;

  glm::vec3 getLocalPosition() const;
  glm::vec3 getWorldPosition() const;
  glm::quat getRotation() const;
  glm::vec3 getScale() const;

  void rotate(float angle_degrees, const glm::vec3 &axis);
  void translate(const glm::vec3 &offset);
  void applyScale(const glm::vec3 &factor);

  void setLocalPosition(const glm::vec3 &position);
  void setWorldPosition(const glm::vec3 &position);
  void setRotation(const glm::quat &newRotation);
  void setScale(const glm::vec3 &scale);

  void addChild(Transform *child);
  void removeChild(Transform *child);
  void setParent(Transform *newParent);

  std::vector<Transform *> getChildren() const;
  Transform *getNthChild(size_t n) const;
  Transform *getParent() const;

private:
  Transform *parent;
  std::vector<Transform *> children;

  glm::vec3 position;
  glm::quat rotation;
  glm::vec3 scale;

  mutable glm::mat4 localTransformMatrix;
  mutable glm::mat4 worldTransformMatrix;
  mutable bool isLocalDirty;
  mutable bool isWorldDirty;

  glm::mat4 calculateLocalMatrix() const;
  void setLocalDirty();
  void setWorldDirty();
};
} // namespace BBong
#endif // TRANSFORM_HPP