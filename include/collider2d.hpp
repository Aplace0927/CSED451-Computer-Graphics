#ifndef COLLIDER2D_HPP
#define COLLIDER2D_HPP

#include <stdexcept>
#include "component.hpp"
#include "transform.hpp"
#include "boundingbox2d.hpp"
#include "meshrenderer2d.hpp"

namespace Component {
class Collider2D : public Component {
protected:
  Data::BoundingBox2D *boundingBox;

protected:
  explicit Collider2D(GameObject::GameObject *owner)
      : Component(owner), boundingBox(nullptr) {}

  void fixedUpdate() override {
    if (boundingBox)
      boundingBox->updateWorld(transform->getWorldMatrix());
  }

  bool intersects(const Collider2D *other) const {
    return this->boundingBox->intersects(*other->boundingBox);
  }

  const Data::BoundingBox2D *getBoundingBox() const { return boundingBox; }
};

class MeshCollider2D : public Collider2D {
public:
  explicit MeshCollider2D(GameObject::GameObject *owner) : Collider2D(owner) {
    MeshRenderer2D *meshRenderer = getComponent<MeshRenderer2D>();
    if (!meshRenderer)
      throw std::runtime_error("MeshCollider2D requires a MeshRenderer2D "
                               "component on the same GameObject.");

    this->boundingBox = meshRenderer->getBoundingbox();
  }

protected:
  void update() override {}
};
} // namespace Component

#endif // COLLIDER2D_HPP
