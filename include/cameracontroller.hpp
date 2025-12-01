#ifndef CameraManager_HPP
#define CameraManager_HPP

#include <iostream>
#include <map>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include "BBong/component.hpp"
#include "BBong/gameobject.hpp"
#include "BBong/camera.hpp"
#include "BBong/inputmanager.hpp"

namespace BBong {
class CameraController : public ClonableComponent<CameraController> {
public:
  explicit CameraController(GameObject *owner) : ClonableComponent(owner) {}

  CameraController(const CameraController &other)
      : ClonableComponent(nullptr), cameras(other.cameras) {}

  void setCamera(ProjectionMode mode, Camera *camera) {
    cameras[mode] = camera;
  }

  void update() override {
    if (currentMode != Input::getInstance().projectionMode) {

      if (shaking) {
        Camera *prevCam = getActiveCamera();
        if (prevCam) {
          prevCam->transform->setLocalPosition(originalCameraPos);
        }
      }

      currentMode = Input::getInstance().projectionMode;

      Camera *activeCam = getActiveCamera();
      if (activeCam) {
        GraphicsManager::getInstance().setMainCamera(activeCam);

        if (shaking) {
          originalCameraPos = activeCam->transform->getLocalPosition();
        }
      }
    }
  }

  void lateUpdate() override {
    if (shaking) {
      shakeTimer -= Utility::DeltaTime;

      Camera *activeCam = getActiveCamera();
      if (!activeCam)
        return;

      if (shakeTimer <= 0.0f) {
        shaking = false;
        shakeTimer = 0.0f;
        activeCam->transform->setLocalPosition(originalCameraPos);
      } else {
        applyCameraShake(activeCam);
      }
    }
  }

  void startCameraShake(float duration, float magnitude, float speed) {
    Camera *activeCam = getActiveCamera();
    if (activeCam) {
      originalCameraPos = activeCam->transform->getLocalPosition();
    }

    shakeDuration = duration;
    shakeMagnitude = magnitude;
    shakeSpeed = speed;
    shakeTimer = duration;
    shaking = true;
  }

  void applyCameraShake(Camera *camera) const {
    if (!camera)
      return;

    float randomX = ((float)rand() / (RAND_MAX)) * 2.0f - 1.0f;
    float randomY = ((float)rand() / (RAND_MAX)) * 2.0f - 1.0f;

    float offsetX = randomX * shakeMagnitude / GameConfig::WINDOW_WIDTH;
    float offsetY = randomY * shakeMagnitude / GameConfig::WINDOW_HEIGHT;

    camera->transform->setLocalPosition(originalCameraPos +
                                        glm::vec3(offsetX, offsetY, 0.0f));
  }

private:
  Camera *getActiveCamera() {
    auto it = cameras.find(currentMode);
    if (it != cameras.end()) {
      return it->second;
    }
    return nullptr;
  }

private:
  ProjectionMode currentMode = ProjectionMode::NONE;

  std::map<ProjectionMode, Camera *> cameras;

  glm::vec3 originalCameraPos;

  bool shaking = false;
  float shakeDuration = 0.0f;
  float shakeTimer = 0.0f;
  float shakeMagnitude = 0.0f;
  float shakeSpeed = 0.0f;
};
}; // namespace BBong
#endif // CameraManager_HPP