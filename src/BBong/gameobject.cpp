#include "BBong/gameobject.hpp"

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

namespace BBong {
GameObject::GameObject(Transform *parent) {
  transform = addComponent<Transform>();

  if (parent) {
    parent->addChild(transform);
    transform->setParent(parent);
  }

  m_isActive = true;
}

void GameObject::cloneComponentsFrom(const GameObject &other) {
  m_components.clear();
  transform = nullptr;

  m_components.reserve(other.m_components.size());
  for (const auto &compPtr : other.m_components) {
    auto newComponent = compPtr->clone(this);

    Transform *newTransform = dynamic_cast<Transform *>(newComponent.get());
    if (newTransform) {
      transform = newTransform;
    }

    m_components.push_back(std::move(newComponent));
  }

  if (!transform) {
    transform = addComponent<Transform>();
  }
}

void GameObject::cloneFrom(const GameObject &other, Transform *parent) {
  m_isActive = other.m_isActive;
  cloneComponentsFrom(other);
  if (parent) {
    parent->addChild(transform);
    transform->setParent(parent);
  }
}

#pragma region func
void GameObject::fixedUpdate() {
  if (!m_isActive)
    return;
  for (const auto &comp : m_components) {
    comp->doFixedUpdate();
  }
  for (auto child : transform->getChildren()) {
    child->gameObject->fixedUpdate();
  }
}

void GameObject::collision() {
  if (!m_isActive)
    return;
  for (const auto &comp : m_components) {
    comp->doCollision();
  }
  for (auto child : transform->getChildren()) {
    child->gameObject->collision();
  }
}

void GameObject::update() {
  if (!m_isActive)
    return;
  for (const auto &comp : m_components) {
    comp->doUpdate();
  }
  for (auto child : transform->getChildren()) {
    child->gameObject->update();
  }
}

void GameObject::lateUpdate() {
  if (!m_isActive)
    return;
  for (const auto &comp : m_components) {
    comp->doLateUpdate();
  }
  for (auto child : transform->getChildren()) {
    child->gameObject->lateUpdate();
  }
}

void GameObject::renderUpdate() {
  if (!m_isActive)
    return;
  glPushMatrix();
  glMultMatrixf(glm::value_ptr(transform->getLocalMatrix()));
  for (const auto &comp : m_components) {
    comp->doRenderUpdate();
  }
  for (auto child : transform->getChildren()) {
    child->gameObject->renderUpdate();
  }
  glPopMatrix();
}
#pragma endregion
} // namespace BBong