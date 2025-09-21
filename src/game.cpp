#include "game.hpp"

Game::Game::Game() {
    player = Player::Player();
    enemy = Enemy::Enemy();
    playerMoveVec = glm::vec3(0.0f, 0.0f, 0.0f);

    player.setBulletHitDetectFunction(enemy.getBoundingBoxCollisionFunction());
    player.setBulletHitEventFunction(enemy.getBulletHitDetectHandlerFunction());
    enemy.setBulletHitDetectFunction(player.getBoundingBoxCollisionFunction());
    enemy.setBulletHitEventFunction(player.getBulletHitDetectHandlerFunction());
}

Game::Game::~Game() {}
void Game::Game::keyEvent(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
            playerMoveVec.y ++;
            player.setDirection(Utils::getNormalizedDirection(playerMoveVec, GameConfig::PLAYER_SPEED));
            break;
        case 's':
            playerMoveVec.y --;
            player.setDirection(Utils::getNormalizedDirection(playerMoveVec, GameConfig::PLAYER_SPEED));
            break;
        case 'a':
            playerMoveVec.x --;
            player.setDirection(Utils::getNormalizedDirection(playerMoveVec, GameConfig::PLAYER_SPEED));
            break;
        case 'd':
            playerMoveVec.x ++;
            player.setDirection(Utils::getNormalizedDirection(playerMoveVec, GameConfig::PLAYER_SPEED));
            break;
        case 'q':
            glutSetKeyRepeat(GLUT_KEY_REPEAT_DEFAULT);
            exit(0);
        case ' ':
            player.shooting(true);
            break;
        default:
            break;
    }
}

void Game::Game::keyUpEvent(unsigned char key, int x, int y) {
    // Handle key release events if needed
    switch (key) {
        case 'w':
            playerMoveVec.y --;
            player.setDirection(Utils::getNormalizedDirection(playerMoveVec, GameConfig::PLAYER_SPEED));
            break;
        case 's':
            playerMoveVec.y ++;
            player.setDirection(Utils::getNormalizedDirection(playerMoveVec, GameConfig::PLAYER_SPEED));
            break;
        case 'a':
            playerMoveVec.x ++;
            player.setDirection(Utils::getNormalizedDirection(playerMoveVec, GameConfig::PLAYER_SPEED));
            break;
        case 'd':
            playerMoveVec.x --;
            player.setDirection(Utils::getNormalizedDirection(playerMoveVec, GameConfig::PLAYER_SPEED));
            break;
        case ' ':
            player.shooting(false);
            break;
        default:
            break;
    }
}