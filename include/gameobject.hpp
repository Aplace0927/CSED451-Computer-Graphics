#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <vector>

#include "component.hpp"
#include "transform.hpp"

namespace GameObject {
class GameObject {
public:
  Component::Transform *transform;

private:
  bool active;
  std::vector<std::unique_ptr<Component::Component>> components;

public:
  GameObject() {
    auto newTransform = std::make_unique<Component::Transform>(this);
    transform = newTransform.get();
    components.push_back(std::move(newTransform));

    active = true;
  }

  ~GameObject() {
  }

  template <typename T> T *addComponent() {
    auto newComponent = std::make_unique<T>(this);
    T *ptr = newComponent.get();
    components.push_back(std::move(newComponent));
    return ptr;
  }

  template <typename T> T *getComponent() {
    for (const auto &comp : components) {
      T *ptr = dynamic_cast<T *>(comp.get());
      if (ptr) {
        return ptr;
      }
    }
    return nullptr;
  }

  bool getStatus() const { return active; }
  void setStatus(bool state) { active = state; }

private:
  friend class Component::Transform;
  void fixedUpdate() {
    for (const auto &comp : components) {
      comp->fixedUpdate();
    }
  }
  void update() {
    for (const auto &comp : components) {
      comp->update();
    }
  }
  void lateUpdate() {
    for (const auto &comp : components) {
      comp->lateUpdate();
    }
  }
  void renderUpdate() {
    for (const auto &comp : components) {
      comp->renderUpdate();
    }
  }
};
} // namespace GameObject

#endif // GAMEOBJECT_HPP