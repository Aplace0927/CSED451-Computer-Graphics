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

  friend class GameObject::GameObject;
  virtual void fixedUpdate() {}
  virtual void update() {}
  virtual void lateUpdate() {}
  virtual void renderUpdate() {}
};
} // namespace Component

#endif // COMPONENT_HPP