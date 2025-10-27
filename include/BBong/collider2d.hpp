#ifndef COLLIDER2D_HPP
#define COLLIDER2D_HPP

#include <stdexcept>
#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include "BBong/component.hpp"
#include "BBong/transform.hpp"
#include "BBong/boundingbox2d.hpp"
#include "BBong/renderer2d.hpp"

namespace BBong {
class Collider2D : public ClonableComponent<Collider2D> {
protected:
  std::unique_ptr<BoundingBox2D> m_boundingbox;

public:
  explicit Collider2D(GameObject *owner)
      : ClonableComponent<Collider2D>(owner), m_boundingbox(nullptr) {}

  Collider2D(const Collider2D &other) : ClonableComponent<Collider2D>(nullptr){
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

  void SetBoundingBox(const std::vector<glm::vec2> &vertices) {
    m_boundingbox = std::make_unique<BoundingBox2D>();
    for (const auto &vertex : vertices) {
      m_boundingbox->expand(vertex);
    }
  }

  bool intersects(const Collider2D *other) const {
    if (!m_boundingbox || !other->m_boundingbox)
      return false;
    return m_boundingbox->intersects(*other->m_boundingbox);
  }
};

class BoxCollider2D : public Collider2D {
public:
  explicit BoxCollider2D(GameObject *owner) : Collider2D(owner) {}
};
} // namespace BBong

#endif // COLLIDER2D_HPP