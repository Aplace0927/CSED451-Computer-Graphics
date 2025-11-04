#include "game.hpp"
#include "player.hpp"
#include "enemy.hpp"

namespace BBong {
Game::Game() : mainScene(new Scene) {}

void Game::Init() {
  auto playerObj = mainScene->createGameObject();
  playerObj->addComponent<Player>();
  // auto enemyObj = mainScene->createGameObject();
  // enemyObj->addComponent<Enemy>();
}
} // namespace BBong