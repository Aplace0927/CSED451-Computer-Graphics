#ifndef COLLIDER3D_HPP
#define COLLIDER3D_HPP

#include <stdexcept>
#include <memory>
#include <vector>
#include <functional>
#include <glm/glm.hpp>
#include <cstdint>

#include "BBong/component.hpp"
#include "BBong/transform.hpp"
#include "BBong/boundingbox3d.hpp"
#include "BBong/renderer3d.hpp"
#include "config.hpp"

namespace BBong {

class CollisionManager;

class Collider3D : public ClonableComponent<Collider3D> {
protected:
  friend class CollisionManager;

  std::unique_ptr<BoundingBox3D> m_boundingbox;
  GameConfig::CollisionLayer m_layer;

public:
  explicit Collider3D(GameObject *owner);
  Collider3D(const Collider3D &other);
  virtual ~Collider3D();

  void setLayer(GameConfig::CollisionLayer layer) { m_layer = layer; }
  GameConfig::CollisionLayer getLayer() const { return m_layer; }

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
  explicit BoxCollider3D(GameObject *owner) : Collider3D(owner) {
    std::vector<glm::vec3> vertices = {
        glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, -0.5f, -0.5f),
        glm::vec3(0.5f, 0.5f, -0.5f),   glm::vec3(-0.5f, 0.5f, -0.5f),
        glm::vec3(-0.5f, -0.5f, 0.5f),  glm::vec3(0.5f, -0.5f, 0.5f),
        glm::vec3(0.5f, 0.5f, 0.5f),    glm::vec3(-0.5f, 0.5f, 0.5f)};

    SetBoundingBox(vertices);
  }
};
} // namespace BBong

#endif // COLLIDER3D_HPP