#include "game.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "backgroundboundingbox.hpp"

namespace BBong {
Game::Game() : mainScene(new Scene) {}

void Game::Init() {
  GameObject *backgroundboundingboxObj = mainScene->createGameObject();
  backgroundboundingboxObj->addComponent<BackgroundBoundingBox>();

  GameObject *playerObj = mainScene->createGameObject();
  playerObj->addComponent<Player>();

  auto enemyObj = mainScene->createGameObject();
  enemyObj->addComponent<Enemy>();
  enemyObj->transform->setWorldPosition(glm::vec3(
      GameConfig::POSITION_LEFT_LIMIT, GameConfig::POSITION_UPPER_LIMIT, 0.0f));

  mainScene->Instantiate(*enemyObj)->transform->setWorldPosition(
      glm::vec3(GameConfig::POSITION_RIGHT_LIMIT,
                GameConfig::POSITION_UPPER_LIMIT, 0.0f));
}
} // namespace BBong