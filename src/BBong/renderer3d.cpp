#include "BBong/renderer3d.hpp"

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

void MeshRenderer3D::setMesh(std::shared_ptr<Mesh3D> mesh) {
  if (!mesh) {
    throw std::invalid_argument("Mesh cannot be null.");
  }
  m_mesh = mesh;
  m_boundingbox = std::make_unique<BoundingBox3D>();

  for (const auto &vertex_position : m_mesh->getVertices()) {
    m_boundingbox->expand(vertex_position.position);
  }
}

void MeshRenderer3D::renderUpdate() {
  if (!m_mesh)
    return;

  m_boundingbox->updateWorld(transform->getWorldMatrix());

  ShaderManager::getInstance().attachProgram();
  glm::mat4 modelMatrix = transform->getWorldMatrix();
  ShaderManager::getInstance().setUniformValue<glm::mat4>("uMat4Model", modelMatrix);
  ShaderManager::getInstance().detachProgram();
  
  if (forcedGraphicStyleMode.has_value()) {
    m_mesh->draw(forcedGraphicStyleMode.value());
    return;
  }
  switch (Input::getInstance().graphicStyleMode) {
  case Input::SOLID:
    m_mesh->draw(GraphicStyle::OPAQUE_POLYGON);
    break;
  case Input::WIREFRAME:
    m_mesh->draw(GraphicStyle::WIREFRAME);
    break;
  }
}
} // namespace BBong