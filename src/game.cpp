#include "game.hpp"

Game::Game::Game() {
  player = new Player::Player();
  enemys = {
      new Enemy::Enemy(glm::vec3(0.0f, GameConfig::POSITION_UPPER_LIMIT, 0.0f), 100.0f),
      new Enemy::Enemy(glm::vec3(0.0f, GameConfig::POSITION_UPPER_LIMIT, 0.0f), -100.0f)};
  playerMoveVec = glm::vec3(0.0f, 0.0f, 0.0f);
  gameState = GameState::PLAYING;
  dialogueBox = DialogueBox::DialogueBox();

  for (auto enemy : enemys) {
    player->setBulletHitDetectFunction(
        enemy->getBoundingBoxCollisionFunction());
    player->setBulletHitEventFunction(
        enemy->getBulletHitDetectHandlerFunction());

    enemy->setBulletHitDetectFunction(
        player->getBoundingBoxCollisionFunction());
    enemy->setBulletHitEventFunction(
        player->getBulletHitDetectHandlerFunction());
  }
}

Game::Game::~Game() {}
void Game::Game::keyEvent(unsigned char key, int x, int y) {
  switch (key) {
  case 'w':
    playerMoveVec.y++;
    player->setDirection(Utility::getNormalizedDirection(
        playerMoveVec, GameConfig::PLAYER_SPEED));
    break;
  case 's':
    playerMoveVec.y--;
    player->setDirection(Utility::getNormalizedDirection(
        playerMoveVec, GameConfig::PLAYER_SPEED));
    break;
  case 'a':
    playerMoveVec.x--;
    player->setDirection(Utility::getNormalizedDirection(
        playerMoveVec, GameConfig::PLAYER_SPEED));
    break;
  case 'd':
    playerMoveVec.x++;
    player->setDirection(Utility::getNormalizedDirection(
        playerMoveVec, GameConfig::PLAYER_SPEED));
    break;
  case 'q':
    glutSetKeyRepeat(GLUT_KEY_REPEAT_DEFAULT);
    exit(0);
  case ' ':
    player->shooting(true);
    break;
  default:
    break;
  }
}

void Game::Game::keyUpEvent(unsigned char key, int x, int y) {
  // Handle key release events if needed
  switch (key) {
  case 'w':
    playerMoveVec.y--;
    player->setDirection(Utility::getNormalizedDirection(
        playerMoveVec, GameConfig::PLAYER_SPEED));
    break;
  case 's':
    playerMoveVec.y++;
    player->setDirection(Utility::getNormalizedDirection(
        playerMoveVec, GameConfig::PLAYER_SPEED));
    break;
  case 'a':
    playerMoveVec.x++;
    player->setDirection(Utility::getNormalizedDirection(
        playerMoveVec, GameConfig::PLAYER_SPEED));
    break;
  case 'd':
    playerMoveVec.x--;
    player->setDirection(Utility::getNormalizedDirection(
        playerMoveVec, GameConfig::PLAYER_SPEED));
    break;
  case ' ':
    player->shooting(false);
    break;
  default:
    break;
  }
}