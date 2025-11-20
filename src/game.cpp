#include "game.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "backgroundboundingbox.hpp"

namespace BBong {
Game::Game() : mainScene(new Scene) {}

void Game::Init() {
  BBong::ShaderManager::getInstance().init();
  
  GameObject *backgroundboundingboxObj = mainScene->createGameObject();
  backgroundboundingboxObj->addComponent<BackgroundBoundingBox>();

  GameObject *playerObj = mainScene->createGameObject();
  playerObj->addComponent<Player>();

  auto enemyObj1 = mainScene->createGameObject();
  enemyObj1->addComponent<Enemy>();
  enemyObj1->transform->setWorldPosition(glm::vec3(
      GameConfig::POSITION_LEFT_LIMIT, GameConfig::POSITION_UPPER_LIMIT, 0.0f));

  auto enemyObj2 = mainScene->createGameObject();
  enemyObj2->addComponent<Enemy>();
  enemyObj2->transform->setWorldPosition(
      glm::vec3(GameConfig::POSITION_RIGHT_LIMIT,
                GameConfig::POSITION_UPPER_LIMIT, 0.0f));
}
} // namespace BBong