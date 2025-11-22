#include "BBong/camera.hpp"
#include "BBong/graphicsmanager.hpp"
#include "config.hpp"
#include <iostream>

namespace BBong {

Camera::Camera(GameObject *owner)
    : ClonableComponent(owner), m_projectionType(ProjectionType::PERSPECTIVE),
      m_orthoSize(10.0f), m_nearPlane(0.1f), m_farPlane(1000.0f),
      m_fov(glm::radians(60.0f)), m_aspectRatio(16.0f / 9.0f),
      m_orthoWidth(1920.0f), m_orthoHeight(1080.0f) {

  m_aspectRatio = static_cast<float>(GameConfig::WINDOW_WIDTH) /
                  static_cast<float>(GameConfig::WINDOW_HEIGHT);
}

Camera::Camera(const Camera &other)
    : ClonableComponent(nullptr), m_projectionType(other.m_projectionType),
      m_orthoSize(other.m_orthoSize), m_nearPlane(other.m_nearPlane),
      m_farPlane(other.m_farPlane), m_fov(other.m_fov),
      m_aspectRatio(other.m_aspectRatio), m_orthoWidth(other.m_orthoWidth),
      m_orthoHeight(other.m_orthoHeight) {}

void Camera::setProjectionType(ProjectionType mode) { m_projectionType = mode; }

glm::mat4 Camera::getViewMatrix() const {
  return glm::inverse(transform->getWorldMatrix());
}

glm::mat4 Camera::getProjectionMatrix() const {
  switch (m_projectionType) {
  case ProjectionType::PERSPECTIVE:
    return glm::perspective(m_fov, m_aspectRatio, m_nearPlane, m_farPlane);
  case ProjectionType::ORTHOGRAPHIC:
    float halfW = m_orthoWidth / 2.0f;
    float halfH = m_orthoHeight / 2.0f;

    return glm::ortho(-halfW, halfW, -halfH, halfH, m_nearPlane, m_farPlane);
  }
  return glm::mat4(1.0f);
}

void Camera::setPerspective(float fovRadians, float aspect, float nearPlane,
                            float farPlane) {
  m_fov = fovRadians;
  m_aspectRatio = aspect;
  m_nearPlane = nearPlane;
  m_farPlane = farPlane;
  m_projectionType = ProjectionType::PERSPECTIVE;
}

void Camera::setOrthographic(float width, float height, float nearPlane,
                             float farPlane) {
  m_orthoWidth = width;
  m_orthoHeight = height;
  m_nearPlane = nearPlane;
  m_farPlane = farPlane;
  m_projectionType = ProjectionType::ORTHOGRAPHIC;
}

void Camera::updateAspectRatio(float aspect) { m_aspectRatio = aspect; }
} // namespace BBong