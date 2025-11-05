#ifndef RENDERER3D_HPP
#define RENDERER3D_HPP

#include <memory>
#include <stdexcept>
#include <glm/glm.hpp>

#include "BBong/component.hpp"
#include "BBong/boundingbox3d.hpp"
#include "BBong/mesh3D.hpp"

namespace BBong {
class MeshRenderer3D : public ClonableComponent<MeshRenderer3D> {
private:
  std::shared_ptr<Mesh3D> m_mesh;
  std::unique_ptr<BoundingBox3D> m_boundingbox;

public:
  explicit MeshRenderer3D(GameObject *owner);
  MeshRenderer3D(const MeshRenderer3D &other);

  void SetMesh(std::shared_ptr<Mesh3D> mesh);

  std::shared_ptr<Mesh3D> getMesh() { return m_mesh; }
  const BoundingBox3D *getBoundingbox() const { return m_boundingbox.get(); }

private:
  void renderUpdate() override;
};
} // namespace BBong
#endif // RENDERER3D_HPP