#ifndef MESHRENDERER2D_HPP
#define MESHRENDERER2D_HPP

#include <memory>
#include <stdexcept>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "BBong/component.hpp"
#include "boundingbox2d.hpp"
#include "mesh2d.hpp"

namespace BBong {
class MeshRenderer2D : public ClonableComponent<MeshRenderer2D> {
private:
  std::shared_ptr<Mesh2D> m_mesh;
  std::unique_ptr<BoundingBox2D> m_boundingbox;

public:
  explicit MeshRenderer2D(GameObject *owner) : ClonableComponent(owner) {
    m_boundingbox = std::make_unique<BoundingBox2D>();
    if (m_mesh) {
      for (const auto &vertice : m_mesh->getVectices()) {
        m_boundingbox->expand(vertice.position);
      }
    }
  }

  MeshRenderer2D(const MeshRenderer2D &other) : ClonableComponent(nullptr) {
    this->m_mesh = other.m_mesh;
    if (other.m_boundingbox) {
      this->m_boundingbox = other.m_boundingbox->Clone();
    } else {
      this->m_boundingbox = nullptr;
    }
  }

  void SetMesh(std::shared_ptr<Mesh2D> mesh) {
    if (!mesh) {
      throw std::invalid_argument("Mesh cannot be null.");
    }
    m_mesh = mesh;
    m_boundingbox = std::make_unique<BoundingBox2D>();

    for (const auto &vertex_position : m_mesh->getVectices()) {
      m_boundingbox->expand(vertex_position.position);
    }
  }

  std::shared_ptr<Mesh2D> getMesh() { return m_mesh; }
  const BoundingBox2D *getBoundingbox() const { return m_boundingbox.get(); }

private:
  void renderUpdate() override {
    if (!m_mesh)
      return;

    m_boundingbox->updateWorld(transform->getWorldMatrix());
    m_mesh->draw();
  }
};
} // namespace BBong

#endif // MESHRENDERER2D_HPP