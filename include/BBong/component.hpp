#ifndef BBONG_COMPONENT_HPP
#define BBONG_COMPONENT_HPP

#include <memory>
#include <type_traits>

namespace BBong {
class GameObject;
class Transform;
class Collider3D;

class Component {
public:
  GameObject *gameObject;
  Transform *transform;

  explicit Component(GameObject *owner);
  virtual ~Component() = default;

protected:
  template <typename T> T *addComponent();
  template <typename T> T *getComponent();

  bool getActive() const;
  void setActive(bool state);

private:
  friend class GameObject;
  friend class CollisionManager;
  friend class Scene;

  void doFixedUpdate();
  void doCollision3D(Collider3D *collider);
  void doUpdate();
  void doLateUpdate();
  void doRenderUpdate();

  virtual std::unique_ptr<Component> clone(GameObject *newOwner) const = 0;

  virtual void fixedUpdate() {}
  virtual void collision3D(Collider3D *collider) {}
  virtual void update() {}
  virtual void lateUpdate() {}
  virtual void renderUpdate() {}
};

template <typename T> class ClonableComponent : public Component {
public:
  explicit ClonableComponent(GameObject *owner) : Component(owner) {}
  std::unique_ptr<Component> clone(GameObject *newOwner) const override;
};
}; // namespace BBong

#include "BBong/component.inl"

#endif // BBONG_COMPONENT_HPP