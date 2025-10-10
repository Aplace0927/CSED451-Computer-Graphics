#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <vector>
#include <glm/gtc/type_ptr.hpp>

#include "scene.hpp"
#include "transform.hpp"
#include "graphicsmanager.hpp"
#include "physicsmanager.hpp"

namespace GameObject {
class GameObject {
public:
  Component::Transform *transform;

private:
  bool m_isActive;
  std::vector<std::unique_ptr<Component::Component>> m_components;

public:
  GameObject(Component::Transform *parent) {
    auto newTransform = std::make_unique<Component::Transform>(this);
    transform = newTransform.get();
    m_components.push_back(std::move(newTransform));

    if (parent) {
      parent->addChild(transform);
      transform->setParent(parent);
    }

    m_isActive = true;
  }

  ~GameObject() {}

  template <typename T> T *addComponent() {
    static_assert(std::is_base_of_v<Component::Component, T>,
                  "T must be a class derived from Component::Component");
    auto newComponent = std::make_unique<T>(this);
    T *ptr = newComponent.get();
    m_components.push_back(std::move(newComponent));
    return ptr;
  }
  template <typename T> T *getComponent() {
    static_assert(std::is_base_of_v<Component::Component, T>,
                  "T must be a class derived from Component::Component");
    for (const auto &comp : m_components) {
      T *ptr = dynamic_cast<T *>(comp.get());
      if (ptr) {
        return ptr;
      }
    }
    return nullptr;
  }

  bool getActive() const { return m_isActive; }
  void setActive(bool state) { m_isActive = state; }

private:
  friend class EngineManager::Scene;
  friend class GameObject;
  void fixedUpdate() {
    for (const auto &comp : m_components) {
      comp->doFixedUpdate();
    }
    for (const auto child : transform->getChildren()) {
      child->gameObject->fixedUpdate();
    }
  }
  void collision() {
    for (const auto &comp : m_components) {
      comp->doCollision();
    }
    for (const auto child : transform->getChildren()) {
      child->gameObject->collision();
    }
  }
  void update() {
    for (const auto &comp : m_components) {
      comp->doUpdate();
    }
    for (const auto child : transform->getChildren()) {
      child->gameObject->update();
    }
  }
  void lateUpdate() {
    for (const auto &comp : m_components) {
      comp->doLateUpdate();
    }
    for (const auto child : transform->getChildren()) {
      child->gameObject->lateUpdate();
    }
  }
  void renderUpdate() {
    glPushMatrix();
    glMultMatrixf(glm::value_ptr(transform->getLocalMatrix()));
    for (const auto &comp : m_components) {
      comp->doRenderUpdate();
    }
    for (const auto child : transform->getChildren()) {
      child->gameObject->renderUpdate();
    }
    glPopMatrix();
  }
};
} // namespace GameObject

#endif // GAMEOBJECT_HPP