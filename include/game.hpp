#ifndef GAME_HPP
#define GAME_HPP

#include <GL/freeglut.h>
#include <GL/glew.h>
#include <chrono>
#include <functional>
#include <glm/glm.hpp>
#include <iostream>

#include "bullet.hpp"
#include "enemy.hpp"
#include "objectpool.hpp"
#include "player.hpp"
#include "singleton.hpp"
#include "utility.hpp"

namespace Game {
class Game : public Singleton::Singleton<Game> {
public:
  Game();
  ~Game();
  void keyEvent(unsigned char key, int x, int y);
  void keyUpEvent(unsigned char key, int x, int y);

private:
  Player::Player player;
  glm::vec3 playerMoveVec;

  Enemy::Enemy enemy;
};
}; // namespace Game

#endif // GAME_HPP