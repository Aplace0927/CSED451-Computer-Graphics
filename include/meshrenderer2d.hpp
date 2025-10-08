#ifndef MESHRENDERER2D_HPP
#define MESHRENDERER2D_HPP

#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "component.hpp"
#include "transform.hpp"
#include "boundingbox2d.hpp"
#include "mesh2d.hpp"

namespace Component {
class MeshRenderer2D : public Component {
private:
  Data::Mesh2D *mesh;
  Data::BoundingBox2D *boundingbox;

public:
  explicit MeshRenderer2D(GameObject::GameObject *owner,
                        Data::Mesh2D *mesh)
      : Component(owner), mesh(mesh) {
    if (!mesh)
      throw std::runtime_error("Rederer2D's Mesh object is null");
    // TODO: make a boundingbox
  }

  void renderUpdate() override {
    //TODO: check collision Rederer boundingbox and Camera boundingbox -> optim
    mesh->draw();
  }
};
} // namespace Component

#endif // MESHRENDERER2D_HPP