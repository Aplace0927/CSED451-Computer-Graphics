#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <vector>

#include "scene.hpp"
#include "component.hpp"
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
    auto newComponent = std::make_unique<T>(this);
    T *ptr = newComponent.get();
    m_components.push_back(std::move(newComponent));
    return ptr;
  }
  template <typename T> T *getComponent() {
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
  void fixedUpdate() {
    for (const auto &comp : m_components) {
      comp->fixedUpdate();
    }
  }
  void update() {
    for (const auto &comp : m_components) {
      comp->update();
    }
  }
  void lateUpdate() {
    for (const auto &comp : m_components) {
      comp->lateUpdate();
    }
  }
  void renderUpdate() {
    glPushMatrix();
    glMultMatrixf(glm::value_ptr(transform->GetModelMatrix()));
    for (const auto &comp : m_components) {
      comp->renderUpdate();
    }
    glPopMatrix();
  }
};
} // namespace GameObject

#endif // GAMEOBJECT_HPP