#include "game.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "backgroundboundingbox.hpp"

namespace BBong {
Game::Game() : mainScene(new Scene) {}

void Game::Init() {
  GameObject* backgroundboundingboxObj = mainScene->createGameObject();
  backgroundboundingboxObj->addComponent<BackgroundBoundingBox>();

  GameObject* playerObj = mainScene->createGameObject();
  playerObj->addComponent<Player>();
  /*auto enemyObj = mainScene->createGameObject();
  enemyObj->addComponent<Enemy>();*/
}
} // namespace BBong