#ifndef MESHCOLLIDER2D_HPP
#define MESHCOLLIDER2D_HPP

#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "component.hpp"
#include "transform.hpp"
#include "boundingbox2d.hpp"
#include "meshrenderer2d.hpp"

namespace Component {
class MeshCollider2D : public Component {
private:
  Data::Mesh2D mesh;
  Data::BoundingBox2D boundingbox;

public:
  explicit MeshCollider2D(GameObject::GameObject *owner,
                          MeshRenderer2D *meshRederer2d)
      : Component(owner), mesh(meshRederer2d->mesh),
        boundingbox(meshRederer2d->boundingbox) {
    if (!meshRederer2d)
      throw std::runtime_error("Collider2D's MeshRederer object is null");
  }

  void renderUpdate() override {
    // check collision Rederer boundingbox and Camera boundingbox -> optim
    mesh->draw();
  }
};
} // namespace Component

#endif // MESHCOLLIDER2D_HPP