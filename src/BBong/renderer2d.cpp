#include "BBong/renderer2d.hpp"

#include "BBong/gameobject.hpp"
#include "BBong/transform.hpp"

namespace BBong {
MeshRenderer2D::MeshRenderer2D(GameObject *owner) : ClonableComponent(owner) {
  m_boundingbox = std::make_unique<BoundingBox2D>();
}

MeshRenderer2D::MeshRenderer2D(const MeshRenderer2D &other)
    : ClonableComponent(nullptr) {
  this->m_mesh = other.m_mesh;
  if (other.m_boundingbox) {
    this->m_boundingbox = other.m_boundingbox->Clone();
  } else {
    this->m_boundingbox = nullptr;
  }
}

void MeshRenderer2D::SetMesh(std::shared_ptr<Mesh2D> mesh) {
  if (!mesh) {
    throw std::invalid_argument("Mesh cannot be null.");
  }
  m_mesh = mesh;
  m_boundingbox = std::make_unique<BoundingBox2D>();

  for (const auto &vertex_position : m_mesh->getVectices()) {
    m_boundingbox->expand(vertex_position.position);
  }
}

void MeshRenderer2D::renderUpdate() {
  if (!m_mesh)
    return;

  m_boundingbox->updateWorld(transform->getWorldMatrix());
  m_mesh->draw();
}
} // namespace BBong