#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "gameobject.hpp"

namespace Component {
class Component {
public:
  GameObject::GameObject *gameObject;
  virtual ~Component() = default;

protected:
  explicit Component(GameObject::GameObject *owner) : gameObject(owner) {}

  friend class GameObject::GameObject;
  virtual void fixedUpdate() {}
  virtual void update() {}
  virtual void lateUpdate() {}
  virtual void renderUpdate() {}
};
} // namespace GameObject

#endif // COMPONENT_HPP