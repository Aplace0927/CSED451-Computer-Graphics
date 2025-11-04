#ifndef RENDERER3D_HPP
#define RENDERER3D_HPP

#include <memory>
#include <glm/glm.hpp>
#include <GL/gl.h>
#include "BBong/Mesh3D.hpp"

namespace BBong {
class Render3D {
public:
  Render3D(std::shared_ptr<Mesh3D> mesh)
      : m_mesh(mesh), position(0.0f), rotation(0.0f), scale(1.0f) {}

  void render(GraphicStyle style) {
    if (!m_mesh)
      return;
    glPushMatrix();

    glTranslatef(position.x, position.y, position.z);

    glRotatef(rotation.z, 0.0f, 0.0f, 1.0f);
    glRotatef(rotation.y, 0.0f, 1.0f, 0.0f);
    glRotatef(rotation.x, 1.0f, 0.0f, 0.0f);

    glScalef(scale.x, scale.y, scale.z);

    m_mesh->draw(style);

    glPopMatrix();
  }

  void setMesh(std::shared_ptr<Mesh3D> mesh) { m_mesh = mesh; }

private:
  std::shared_ptr<Mesh3D> m_mesh;
};
} // namespace BBong
#endif // RENDERER3D_HPP