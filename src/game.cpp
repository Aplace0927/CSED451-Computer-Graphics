#include "game.hpp"

Game::Game::Game() {
    player = Player::Player();
    enemy = Enemy::Enemy();
    playerMoveVec = glm::vec3(0.0f, 0.0f, 0.0f);

    player.setBulletHitDetectFunction(enemy.getBoundingBoxCollisionFunction());
    player.setBulletHitEventFunction(enemy.getBulletHitDetectHandlerFunction());
}

// void Game::Game::draw() {
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
//     uint64_t current_time = std::chrono::duration_cast<std::chrono::milliseconds>(
//         std::chrono::system_clock::now().time_since_epoch()
//     ).count();

//     GraphicsManager::GraphicsManager::getInstance().registerHandler(player);

//     for (auto& bullet : bullets) {
//         bullet.draw(current_time);
//         printf("%.4f %.4f\n", bullet.getCenter().x, bullet.getCenter().y);
//     }
    
    
//     //!TODO: add game objects drawing here
//     glutSwapBuffers();
//     glutPostRedisplay();
// }

Game::Game::~Game() {}
void Game::Game::keyEvent(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
            playerMoveVec.y ++;
            player.setDirection(Movement::getNormalizedDirection(playerMoveVec, GameConfig::PLAYER_SPEED));
            break;
        case 's':
            playerMoveVec.y --;
            player.setDirection(Movement::getNormalizedDirection(playerMoveVec, GameConfig::PLAYER_SPEED));
            break;
        case 'a':
            playerMoveVec.x --;
            player.setDirection(Movement::getNormalizedDirection(playerMoveVec, GameConfig::PLAYER_SPEED));
            break;
        case 'd':
            playerMoveVec.x ++;
            player.setDirection(Movement::getNormalizedDirection(playerMoveVec, GameConfig::PLAYER_SPEED));
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
            player.setDirection(Movement::getNormalizedDirection(playerMoveVec, GameConfig::PLAYER_SPEED));
            break;
        case 's':
            playerMoveVec.y ++;
            player.setDirection(Movement::getNormalizedDirection(playerMoveVec, GameConfig::PLAYER_SPEED));
            break;
        case 'a':
            playerMoveVec.x ++;
            player.setDirection(Movement::getNormalizedDirection(playerMoveVec, GameConfig::PLAYER_SPEED));
            break;
        case 'd':
            playerMoveVec.x --;
            player.setDirection(Movement::getNormalizedDirection(playerMoveVec, GameConfig::PLAYER_SPEED));
            break;
        case ' ':
            player.shooting(false);
        default:
            break;
    }
}