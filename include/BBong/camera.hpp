#pragma once

#include "BBong/component.hpp"
#include "BBong/transform.hpp"
#include "BBong/gameobject.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace BBong {

enum class ProjectionType { PERSPECTIVE, ORTHOGRAPHIC };

class Camera : public ClonableComponent<Camera> {
public:
  explicit Camera(GameObject *owner);
  Camera(const Camera &other);
  ~Camera() override = default;

  glm::mat4 getViewMatrix() const;
  glm::mat4 getProjectionMatrix() const;

  void setProjectionType(ProjectionType mode);
  ProjectionType getProjectionType() const { return m_projectionType; }

  void setPerspective(float fovRadians, float aspect, float nearPlane,
                      float farPlane);
  void setOrthographic(float width, float height, float nearPlane,
                       float farPlane);

  void updateAspectRatio(float aspect);

private:
  ProjectionType m_projectionType;

  // 공통/Perspective 변수
  float m_fov;         // Field of View (Radians)
  float m_aspectRatio; // Width / Height
  float m_nearPlane;
  float m_farPlane;

  // Orthographic 변수
  float m_orthoWidth;
  float m_orthoHeight;
  float m_orthoSize;
};
} // namespace BBong