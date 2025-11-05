#ifndef COLLIDER3D_HPP
#define COLLIDER3D_HPP

#include <stdexcept>
#include <memory>
#include <vector>
#include <glm/glm.hpp>

#include "BBong/component.hpp"
#include "BBong/transform.hpp"
#include "BBong/boundingbox3d.hpp"
#include "BBong/renderer3d.hpp"

namespace BBong {
class Collider3D : public ClonableComponent<Collider3D> {
protected:
  std::unique_ptr<BoundingBox3D> m_boundingbox;

public:
  explicit Collider3D(GameObject *owner)
      : ClonableComponent<Collider3D>(owner), m_boundingbox(nullptr) {}

  Collider3D(const Collider3D &other) : ClonableComponent<Collider3D>(nullptr) {
    if (other.m_boundingbox) {
      this->m_boundingbox = other.m_boundingbox->Clone();
    } else {
      this->m_boundingbox = nullptr;
    }
  }

protected:
  void fixedUpdate() override {
    if (m_boundingbox)
      m_boundingbox->updateWorld(transform->getWorldMatrix());
  }

  void SetBoundingBox(const std::vector<glm::vec3> &vertices) {
    m_boundingbox = std::make_unique<BoundingBox3D>();
    for (const auto &vertex : vertices) {
      m_boundingbox->expand(vertex);
    }
  }

  bool intersects(const Collider3D *other) const {
    if (!m_boundingbox || !other->m_boundingbox)
      return false;
    return m_boundingbox->intersects(*other->m_boundingbox);
  }
};

class BoxCollider3D : public Collider3D {
public:
  explicit BoxCollider3D(GameObject *owner) : Collider3D(owner) {}
};
} // namespace BBong

#endif // COLLIDER3D_HPP