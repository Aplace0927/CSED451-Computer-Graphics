#include "game.hpp"
#include "player.hpp"
#include "enemy.hpp"

BBong::Game::Game() {
  mainScene = new Scene();

  auto playerObj = mainScene->createGameObject();
  playerObj->addComponent<Player>();
  auto enemyObj = mainScene->createGameObject();
  enemyObj->addComponent<Enemy>();
}