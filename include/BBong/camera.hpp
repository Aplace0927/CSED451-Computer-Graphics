#pragma once

#include "BBong/component.hpp"
#include "BBong/transform.hpp"
#include "BBong/gameobject.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace BBong {

enum class ProjectionType {
  PERSPECTIVE,
  ORTHOGRAPHIC
};

class Camera : public ClonableComponent<Camera> {
public:
  explicit Camera(GameObject *owner);
  Camera(const Camera &other);
  virtual ~Camera();

  void lateUpdate() override;

  glm::mat4 getViewMatrix() const;

  glm::mat4 getProjectionMatrix() const;

  void onResize(int width, int height);

  void setProjectionType(ProjectionType pt);
  ProjectionType getProjectionType() const { return m_projectionType; }

private:
  ProjectionType m_projectionType;

  int m_width;
  int m_height;
  float m_aspectRatio;

  float m_fov;
  float m_orthoSize;
  float m_nearPlane;
  float m_farPlane;
};

} // namespace BBong