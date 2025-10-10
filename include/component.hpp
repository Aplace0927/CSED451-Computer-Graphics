#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "gameobject.hpp"

namespace Component {
class Component {
public:
  GameObject::GameObject *gameObject;
  Transform *transform;

  virtual ~Component() = default;

protected:
  explicit Component(GameObject::GameObject *owner)
      : gameObject(owner), transform(owner->transform) {}

  template <typename T> T *addComponent() {
    static_assert(std::is_base_of_v<Component::Component, T>,
                  "T must be a class derived from Component::Component");
    return gameObject->addComponent<T>()
  }
  template <typename T> T *getComponent() {
    static_assert(std::is_base_of_v<Component::Component, T>,
                  "T must be a class derived from Component::Component");
    return gameObject->getComponent<T>()
  }

private:
  friend class GameObject::GameObject;

  void doFixedUpdate() { fixedUpdate(); }
  void doCollision() { collision(); }
  void doUpdate() { update(); }
  void doLateUpdate() { lateUpdate(); }
  void doRenderUpdate() { renderUpdate(); }

  virtual void fixedUpdate() {}
  virtual void collision() {}
  virtual void update() {}
  virtual void lateUpdate() {}
  virtual void renderUpdate() {}
};
} // namespace Component

#endif // COMPONENT_HPP