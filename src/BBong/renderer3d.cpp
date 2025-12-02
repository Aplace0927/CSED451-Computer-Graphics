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
  this->m_texture = other.m_texture;
  this->m_normalMap = other.m_normalMap;
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

  // Model Matrix
  glm::mat4 modelMatrix = transform->getWorldMatrix();
  ShaderManager::getInstance().setUniformValue<glm::mat4>("uMat4Model",
                                                          modelMatrix);

  GLuint texID = m_texture.has_value() ? m_texture.value() : 0;
  GLuint normID = m_normalMap.has_value() ? m_normalMap.value() : 0;

  ShaderManager::getInstance().detachProgram();

  if (forcedGraphicStyleMode.has_value()) {
    m_mesh->draw(forcedGraphicStyleMode.value(), texID, normID);
    return;
  }

  switch (Input::getInstance().graphicStyleMode) {
  case SOLID:
    m_mesh->draw(GraphicStyle::OPAQUE_POLYGON, texID, normID);
    break;
  case WIREFRAME:
    m_mesh->draw(GraphicStyle::WIREFRAME, texID, normID);
    break;
  case HIDDEN_LINE_REMOVAL:
    m_mesh->draw(GraphicStyle::HIDDEN_LINE_REMOVAL, texID, normID);
    break;
  }

}
} // namespace BBong