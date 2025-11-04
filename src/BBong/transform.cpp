#include "BBong/transform.hpp"
#include "BBong/gameobject.hpp"

namespace BBong {
std::unique_ptr<Component> Transform::clone(GameObject *newOwner) const {
  auto t = std::make_unique<Transform>(newOwner);
  t->position = position;
  t->rotation = rotation;
  t->scale = scale;
  return t;
}

glm::mat4 Transform::getWorldMatrix() {
  if (isWorldDirty) {
    if (isLocalDirty) {
      localTransformMatrix = calculateLocalMatrix();
      isLocalDirty = false;
    }

    if (parent) {
      worldTransformMatrix = parent->getWorldMatrix() * localTransformMatrix;
    } else {
      worldTransformMatrix = localTransformMatrix;
    }

    isWorldDirty = false;
  }
  return worldTransformMatrix;
}

glm::mat4 Transform::getLocalMatrix() {
  if (isLocalDirty) {
    localTransformMatrix = calculateLocalMatrix();
    isLocalDirty = false;
  }
  return localTransformMatrix;
}

void Transform::rotate(float angle_degrees, const glm::vec3 &axis) {
  rotation = glm::angleAxis(glm::radians(angle_degrees), axis) * rotation;
  rotation = glm::normalize(rotation);
  setLocalDirty();
}

void Transform::translate(const glm::vec3 &offset) {
  position += offset;
  setLocalDirty();
}

void Transform::applyScale(const glm::vec3 &factor) {
  scale *= factor;
  setLocalDirty();
}

void Transform::setRotation(const glm::quat &newRotation) {
  this->rotation = glm::normalize(newRotation);
  setLocalDirty();
}

void Transform::setPosition(const glm::vec3 &position) {
  this->position = position;
  setLocalDirty();
}

void Transform::setScale(const glm::vec3 &scale) {
  this->scale = scale;
  setLocalDirty();
}

void Transform::addChild(Transform *child) {
  if (child && child->parent != this) {
    child->setParent(this);
  }
}

void Transform::removeChild(Transform *child) {
  auto it = std::find(children.begin(), children.end(), child);
  if (it != children.end()) {
    (*it)->setParent(nullptr);
    children.erase(it);
  }
}

std::vector<Transform *> Transform::getChildren() const { return children; }

Transform *Transform::getNthChild(size_t n) const {
  if (n < children.size()) {
    return children[n];
  }
  return nullptr;
}

Transform *Transform::getParent() const { return parent; }

void Transform::setParent(Transform *newParent) {
  if (parent) {
    parent->children.erase(
        std::remove(parent->children.begin(), parent->children.end(), this),
        parent->children.end());
  }

  this->parent = newParent;

  if (newParent) {
    newParent->children.push_back(this);
  }

  setWorldDirty();
}

glm::mat4 Transform::calculateLocalMatrix() const {
  glm::mat4 translateMatrix = glm::translate(position);
  glm::mat4 rotationMatrix = glm::mat4_cast(rotation);
  glm::mat4 scaleMatrix = glm::scale(scale);
  return translateMatrix * rotationMatrix * scaleMatrix;
}

void Transform::setLocalDirty() {
  this->isLocalDirty = true;
  setWorldDirty();
}

void Transform::setWorldDirty() {
  if (isWorldDirty) {
    return;
  }

  this->isWorldDirty = true;
  for (Transform *child : children) {
    child->setWorldDirty();
  }
}
} // namespace BBong