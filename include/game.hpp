#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <functional>
#include <chrono>

#include "BBong/singleton.hpp"
#include "BBong/scene.hpp"
#include "utility.hpp"
#include "gamestate.hpp"

extern BBong::GameState gameState;

namespace BBong {
class Game : public Singleton<Game> {
public:
  Game();
  Scene *mainScene;
};
}; // namespace Game
#endif // GAME_HPP