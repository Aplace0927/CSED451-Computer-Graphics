#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>

#include "BBong/singleton.hpp"
#include "BBong/scene.hpp"
#include "cameracontroller.hpp"

namespace BBong {
class Game : public Singleton<Game> {
  friend class Singleton<Game>;

public:
  Scene *mainScene;
  CameraController *cameraController;
  void Init();

private:
  Game();
  void LightInit();
  void CameraInit();

  GameObject *playerObj;
};
} // namespace BBong
#endif // GAME_HPP