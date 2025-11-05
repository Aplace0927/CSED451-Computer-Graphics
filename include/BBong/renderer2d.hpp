#ifndef RENDERER2D_HPP
#define RENDERER2D_HPP

#include <memory>
#include <stdexcept>
#include <glm/glm.hpp>

#include "BBong/component.hpp"
#include "BBong/boundingbox2d.hpp"
#include "BBong/mesh2d.hpp"

namespace BBong {
class Transform;

class MeshRenderer2D : public ClonableComponent<MeshRenderer2D> {
private:
  std::shared_ptr<Mesh2D> m_mesh;
  std::unique_ptr<BoundingBox2D> m_boundingbox;

public:
  explicit MeshRenderer2D(GameObject *owner);
  MeshRenderer2D(const MeshRenderer2D &other);

  void SetMesh(std::shared_ptr<Mesh2D> mesh);

  std::shared_ptr<Mesh2D> getMesh() { return m_mesh; }
  const BoundingBox2D *getBoundingbox() const { return m_boundingbox.get(); }

private:
  void renderUpdate() override;
};
} // namespace BBong

#endif // RENDERER2D_HPP