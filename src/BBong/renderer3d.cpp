#include "BBong/renderer3d.hpp"

#include "BBong/gameobject.hpp"
#include "BBong/transform.hpp"

namespace BBong {
MeshRenderer3D::MeshRenderer3D(GameObject *owner) : ClonableComponent(owner) {
  m_boundingbox = std::make_unique<BoundingBox3D>();
}

MeshRenderer3D::MeshRenderer3D(const MeshRenderer3D &other)
    : ClonableComponent(nullptr) {
  this->m_mesh = other.m_mesh;
  if (other.m_boundingbox) {
    this->m_boundingbox = other.m_boundingbox->Clone();
  } else {
    this->m_boundingbox = nullptr;
  }
}

void MeshRenderer3D::SetMesh(std::shared_ptr<Mesh3D> mesh) {
  if (!mesh) {
    throw std::invalid_argument("Mesh cannot be null.");
  }
  m_mesh = mesh;
  m_boundingbox = std::make_unique<BoundingBox3D>();

  for (const auto &vertex_position : m_mesh->getVectices()) {
    m_boundingbox->expand(vertex_position.position);
  }
}

void MeshRenderer3D::renderUpdate() {
  if (!m_mesh)
    return;

  m_boundingbox->updateWorld(transform->getWorldMatrix());
  m_mesh->draw(GraphicStyle::OPAQUE_POLYGON);
}
} // namespace BBong