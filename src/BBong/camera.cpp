#include "BBong/camera.hpp"
#include "config.hpp"
#include <iostream>

namespace BBong {

Camera::Camera(GameObject *owner)
    : ClonableComponent(owner), m_projectionType(ProjectionType::PERSPECTIVE),
      m_width(GameConfig::WINDOW_WIDTH), m_height(GameConfig::WINDOW_HEIGHT),
      m_fov(45.0f), m_orthoSize(10.0f), m_nearPlane(0.1f), m_farPlane(100.0f) {
  if (m_height != 0) {
    m_aspectRatio = static_cast<float>(m_width) / static_cast<float>(m_height);
  } else {
    m_aspectRatio = 1.0f;
  }
}

void Camera::setProjectionType(ProjectionType pt) {
  m_projectionType = pt;
}

void Camera::onResize(int width, int height) {
  m_width = width;
  m_height = height;
  if (height != 0) {
    m_aspectRatio = static_cast<float>(width) / static_cast<float>(height);
  }
}

void Camera::lateUpdate() {

  switch (m_projectionType) {
  case ProjectionType::PERSPECTIVE:
  case ProjectionType::ORTHOGRAPHIC:
    desiredPos = glm::vec3(targetPos.x, m_topViewHeight, targetPos.z);
    m_currentFront = glm::vec3(0.0f, -1.0f, 0.0f);
    m_currentUp = glm::vec3(0.0f, 0.0f, -1.0f);
    break;

  case CameraMode::THIRD_PERSON:
    desiredPos = targetPos + glm::vec3(0.0f, m_tpsHeight, m_tpsDistance);

    m_currentFront = glm::normalize(targetPos - desiredPos);
    m_currentUp = glm::vec3(0.0f, 1.0f, 0.0f);
    break;
  }
}

glm::mat4 Camera::getViewMatrix() const {
  return glm::inverse(transform->getWorldMatrix());
}

glm::mat4 Camera::getProjectionMatrix() const {
  if (m_projectionType == ProjectionType::ORTHOGRAPHIC) {
    float halfW = m_orthoSize * m_aspectRatio;
    float halfH = m_orthoSize;
    return glm::ortho(-halfW, halfW, -halfH, halfH, m_nearPlane, m_farPlane);
  } else {
    return glm::perspective(glm::radians(m_fov), m_aspectRatio, m_nearPlane,
                            m_farPlane);
  }
}

} // namespace BBong