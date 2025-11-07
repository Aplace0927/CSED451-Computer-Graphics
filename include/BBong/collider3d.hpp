#ifndef COLLIDER3D_HPP
#define COLLIDER3D_HPP

#include <stdexcept>
#include <memory>
#include <vector>
#include <functional>
#include <glm/glm.hpp>
#include <cstdint>
#include <iostream>

#include "BBong/component.hpp"
#include "BBong/transform.hpp"
#include "BBong/boundingbox3d.hpp"
#include "BBong/renderer3d.hpp"
#include "config.hpp"

namespace BBong {

class CollisionManager;

class Collider3D : public ClonableComponent<Collider3D> {
protected:
  friend class CollisionManager;

  std::unique_ptr<BoundingBox3D> m_boundingbox;
  GameConfig::CollisionLayer m_layer;

public:
  explicit Collider3D(GameObject *owner);
  Collider3D(const Collider3D &other);
  virtual ~Collider3D();

  void setLayer(GameConfig::CollisionLayer layer);
  GameConfig::CollisionLayer getLayer() const { return m_layer; }

  void SetBoundingBox(const std::vector<glm::vec3> &vertices) {
    m_boundingbox = std::make_unique<BoundingBox3D>();
    for (const auto &vertex : vertices) {
      m_boundingbox->expand(vertex);
    }
  }

protected:
  void fixedUpdate() override {
    if (m_boundingbox)
      m_boundingbox->updateWorld(transform->getWorldMatrix());
  }

  void lateUpdate() override {
    if (!m_boundingbox)
      return;

    if (!Input::getInstance().boundingBoxVisible)
      return;
      
    glPushAttrib(GL_ENABLE_BIT | GL_LINE_BIT | GL_CURRENT_BIT);
    glPushMatrix();

    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glLineWidth(2.0f);
    glColor3f(0.0f, 1.0f, 0.0f);

    const glm::vec3 &min = m_boundingbox->getMinWorld();
    const glm::vec3 &max = m_boundingbox->getMaxWorld();

    glBegin(GL_LINE_LOOP);
    glVertex3f(min.x, min.y, min.z);
    glVertex3f(max.x, min.y, min.z);
    glVertex3f(max.x, max.y, min.z);
    glVertex3f(min.x, max.y, min.z);
    glEnd();

    // 2. �޸� (max.z)
    glBegin(GL_LINE_LOOP);
    glVertex3f(min.x, min.y, max.z);
    glVertex3f(max.x, min.y, max.z);
    glVertex3f(max.x, max.y, max.z);
    glVertex3f(min.x, max.y, max.z);
    glEnd();

    // 3. ���ἱ (4��)
    glBegin(GL_LINES);
    glVertex3f(min.x, min.y, min.z);
    glVertex3f(min.x, min.y, max.z);

    glVertex3f(max.x, min.y, min.z);
    glVertex3f(max.x, min.y, max.z);

    glVertex3f(max.x, max.y, min.z);
    glVertex3f(max.x, max.y, max.z);

    glVertex3f(min.x, max.y, min.z);
    glVertex3f(min.x, max.y, max.z);
    glEnd();

    glPopMatrix();
    glPopAttrib();
  }

  bool intersects(const Collider3D *other) const {
    if (!getActive() || !other->getActive())
      return false;
    if (!m_boundingbox || !other->m_boundingbox)
      return false;
    return m_boundingbox->intersects(*other->m_boundingbox);
  }
};

class BoxCollider3D : public Collider3D {
public:
  explicit BoxCollider3D(GameObject *owner) : Collider3D(owner) {
  }
};
} // namespace BBong

#endif // COLLIDER3D_HPP