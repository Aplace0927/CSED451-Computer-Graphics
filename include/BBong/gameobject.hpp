#ifndef BBONG_GAMEOBJECT_HPP
#define BBONG_GAMEOBJECT_HPP

#include <vector>
#include <memory>
#include <type_traits>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/gtc/type_ptr.hpp>

#include "BBong/transform.hpp"
#include "BBong/component.hpp"

namespace BBong {
class Scene;
class GameObject {
public:
  Transform *transform;

private:
  bool m_isActive;
  std::vector<std::unique_ptr<Component>> m_components;

public:
  GameObject(Transform *parent = nullptr) {
    transform = addComponent<Transform>();

    if (parent) {
      parent->addChild(transform);
      transform->setParent(parent);
    }

    m_isActive = true;
  }

  ~GameObject() = default;
  GameObject(const GameObject &) = delete;
  GameObject &operator=(const GameObject &) = delete;

  template <typename T> T *addComponent() {
    static_assert(std::is_base_of_v<Component, T>,
                  "T must be a class derived from BBong::Component");

    auto newComponent = std::make_unique<T>(this);
    T *rawPtr = newComponent.get();
    m_components.push_back(std::move(newComponent));
    return rawPtr;
  }

  template <typename T> T *getComponent() {
    static_assert(std::is_base_of_v<Component, T>,
                  "T must be a class derived from BBong::Component");

    for (const auto &comp : m_components) {
      T *ptr = dynamic_cast<T *>(comp.get());
      if (ptr != nullptr) {
        return ptr;
      }
    }
    return nullptr;
  }

  bool getActive() const { return m_isActive; }
  void setActive(bool state) { m_isActive = state; }

private:
  friend class Scene;

  void cloneComponentsFrom(const GameObject &other) {
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

  void cloneFrom(const GameObject &other, Transform *parent) {
    m_isActive = other.m_isActive;
    cloneComponentsFrom(other);
    if (parent) {
      parent->addChild(transform);
      transform->setParent(parent);
    }
  }

  void fixedUpdate() {
    for (const auto &comp : m_components) {
      comp->doFixedUpdate();
    }
    for (auto child : transform->getChildren()) {
      child->gameObject->fixedUpdate();
    }
  }
  void collision() {
    for (const auto &comp : m_components) {
      comp->doCollision();
    }
    for (auto child : transform->getChildren()) {
      child->gameObject->collision();
    }
  }
  void update() {
    for (const auto &comp : m_components) {
      comp->doUpdate();
    }
    for (auto child : transform->getChildren()) {
      child->gameObject->update();
    }
  }
  void lateUpdate() {
    for (const auto &comp : m_components) {
      comp->doLateUpdate();
    }
    for (auto child : transform->getChildren()) {
      child->gameObject->lateUpdate();
    }
  }
  void renderUpdate() {
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
};
} // namespace BBong

#endif // BBONG_GAMEOBJECT_HPP