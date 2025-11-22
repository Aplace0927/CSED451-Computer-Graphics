#ifndef CAMERACHANGER_HPP
#define CAMERACHANGER_HPP

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include "BBong/component.hpp"
#include "BBong/gameobject.hpp"
#include "BBong/camera.hpp"
#include "BBong/inputmanager.hpp"

namespace BBong {
class CameraChanger : public ClonableComponent<CameraChanger> {
public:
  explicit CameraChanger(GameObject *owner)
      : ClonableComponent(owner),
        TPV_Camera(nullptr),
        Ortho_Camera(nullptr),
        Perspective_Camera(nullptr),
        Player_Camera(nullptr) {}

  CameraChanger(const CameraChanger &other)
      : ClonableComponent(nullptr),
        TPV_Camera(nullptr),
        Ortho_Camera(nullptr),
        Perspective_Camera(nullptr),
        Player_Camera(nullptr) {}

  void update() override {
    if (currentMode != Input::getInstance().projectionMode) {
      currentMode = Input::getInstance().projectionMode;

      switch (currentMode) {
      case PERSPECTIVE:
        GraphicsManager::getInstance().setMainCamera(Perspective_Camera);
        break;
      case ORTHOGRAPHIC:
        GraphicsManager::getInstance().setMainCamera(Ortho_Camera);
        break;
      case TPV_TOPVIEW:
        GraphicsManager::getInstance().setMainCamera(TPV_Camera);
        break;
      case PLAYER_VIEW:
        GraphicsManager::getInstance().setMainCamera(Player_Camera);
        break;
      }
    }
  }

  ProjectionMode currentMode = PERSPECTIVE;
  Camera *TPV_Camera;
  Camera *Ortho_Camera;
  Camera *Perspective_Camera;
  Camera *Player_Camera;
};
}; // namespace BBong
#endif // CAMERACHANGER_HPP