#ifndef RENDERER3D_HPP
#define RENDERER3D_HPP

#include <memory>
#include <optional>
#include <stdexcept>
#include <glm/glm.hpp>

#include "BBong/component.hpp"
#include "BBong/boundingbox3d.hpp"
#include "BBong/gameobject.hpp"
#include "BBong/transform.hpp"
#include "BBong/mesh3d.hpp"
#include "BBong/inputmanager.hpp"
#include "BBong/shadermanager.hpp"

namespace BBong {
class MeshRenderer3D : public ClonableComponent<MeshRenderer3D> {
private:
  std::shared_ptr<Mesh3D> m_mesh;
  std::optional<GLuint> m_texture = std::nullopt;
  std::optional<GLuint> m_normalMap = std::nullopt;
  std::unique_ptr<BoundingBox3D> m_boundingbox;
  std::optional<GraphicStyle> forcedGraphicStyleMode = std::nullopt;

public:
  explicit MeshRenderer3D(GameObject *owner);
  MeshRenderer3D(const MeshRenderer3D &other);

  void setMesh(std::shared_ptr<Mesh3D> mesh);
  void setDefaultColor(const glm::vec3 &color) {
    if (m_mesh) {
      m_mesh->defaultColor = color;
    }
  }
  void setTexture(GLuint texture) { m_texture = texture; }
  void setNormalMap(GLuint normalMap) { m_normalMap = normalMap; }

  std::optional<GLuint> getTextureID() const { return m_texture; }
  std::shared_ptr<Mesh3D> getMesh() { return m_mesh; }
  const BoundingBox3D *getBoundingbox() const { return m_boundingbox.get(); }
  void forceGraphicStyleMode(GraphicStyle style) {
    forcedGraphicStyleMode = style;
  }

private:
  void renderUpdate() override;
};
} // namespace BBong
#endif // RENDERER3D_HPP