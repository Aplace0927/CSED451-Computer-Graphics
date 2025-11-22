#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>

#include "BBong/singleton.hpp"
#include "BBong/scene.hpp"

namespace BBong {
class Game : public Singleton<Game> {
  friend class Singleton<Game>;

public:
  Scene *mainScene;
  void Init();

private:
  Game();
  void CameraInit();

  GameObject *playerObj;
};
} // namespace BBong
#endif // GAME_HPP