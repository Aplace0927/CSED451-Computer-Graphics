#ifndef MESHRENDERER2D_HPP
#define MESHRENDERER2D_HPP

#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "boundingbox2d.hpp"
#include "mesh2d.hpp"

namespace Component {
class MeshRenderer2D : public Component {
private:
  Data::Mesh2D *mesh;
  Data::BoundingBox2D *boundingbox;

public:
  explicit MeshRenderer2D(GameObject::GameObject *owner, Data::Mesh2D *mesh)
      : Component(owner), mesh(mesh) {
    if (!mesh)
      throw std::runtime_error("Rederer2D's Mesh object is null");

    boundingbox = new Data::BoundingBox2D();
    for (const auto &vertice : mesh->getVectices()) {
      boundingbox->expand(vertice.position)
    }
  }

  Data::Mesh2D *getMesh() { return mesh; }
  Data::BoundingBox2D *getBoundingbox() { return boundingbox; }

private:
  void renderUpdate() override {
    boundingbox->updateWorld(transform->getWorldMatrix());

    // TODO: check collision Rederer boundingbox and Camera boundingbox -> optim

    mesh->draw();
  }
};
} // namespace Component

#endif // MESHRENDERER2D_HPP