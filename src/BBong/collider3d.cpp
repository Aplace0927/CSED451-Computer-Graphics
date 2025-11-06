#include "BBong/collider3d.hpp"
#include "BBong/collisionmanager.hpp"

namespace BBong {

Collider3D::Collider3D(GameObject *owner)
    : ClonableComponent<Collider3D>(owner), m_boundingbox(nullptr),
      m_layer(GameConfig::CollisionLayer::NONE) {
  CollisionManager::getInstance().registerCollider3D(this);
}

Collider3D::Collider3D(const Collider3D &other)
    : ClonableComponent<Collider3D>(nullptr), m_layer(other.m_layer) {
  if (other.m_boundingbox) {
    this->m_boundingbox = other.m_boundingbox->Clone();
  } else {
    this->m_boundingbox = nullptr;
  }
  CollisionManager::getInstance().registerCollider3D(this);
}

Collider3D::~Collider3D() {
  CollisionManager::getInstance().unregisterCollider3D(this);
}

} // namespace BBong