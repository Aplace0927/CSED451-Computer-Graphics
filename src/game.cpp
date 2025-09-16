#include "game.hpp"

Game::Game::Game() {
    player = Player::Player();
    enemy = Enemy::Enemy();
    bullets = std::vector<Bullet::Bullet>();

    /*
    TEST EXAMPLE FOR 100 BULLETS
    
    for (int i = 0; i < 100; ++i)
    {
        bullets.push_back(
        Bullet::Bullet(
            glm::vec3(
                -0.25f + (i / 10) * 0.05f, 
                0.25f + (i % 10) * 0.05f, 
                0.0f
            ),
                Enemy::BulletPattern::circular_motion(),
                Bullet::BulletType::PLAYER
            )
        );
    }
    */

    playerMoveVec = glm::vec3(0.0f, 0.0f, 0.0f);
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
            player.setDirection(Movement::getNormalizedDirection(playerMoveVec, GameConfig::playerSpeed));
            break;
        case 's':
            playerMoveVec.y --;
            player.setDirection(Movement::getNormalizedDirection(playerMoveVec, GameConfig::playerSpeed));
            break;
        case 'a':
            playerMoveVec.x --;
            player.setDirection(Movement::getNormalizedDirection(playerMoveVec, GameConfig::playerSpeed));
            break;
        case 'd':
            playerMoveVec.x ++;
            player.setDirection(Movement::getNormalizedDirection(playerMoveVec, GameConfig::playerSpeed));
            break;
        case 'q':
            glutSetKeyRepeat(GLUT_KEY_REPEAT_DEFAULT);
            exit(0);
        default:
            break;
    }
}

void Game::Game::keyUpEvent(unsigned char key, int x, int y) {
    // Handle key release events if needed
    switch (key) {
        case 'w':
            playerMoveVec.y --;
            player.setDirection(Movement::getNormalizedDirection(playerMoveVec, GameConfig::playerSpeed));
            break;
        case 's':
            playerMoveVec.y ++;
            player.setDirection(Movement::getNormalizedDirection(playerMoveVec, GameConfig::playerSpeed));
            break;
        case 'a':
            playerMoveVec.x ++;
            player.setDirection(Movement::getNormalizedDirection(playerMoveVec, GameConfig::playerSpeed));
            break;
        case 'd':
            playerMoveVec.x --;
            player.setDirection(Movement::getNormalizedDirection(playerMoveVec, GameConfig::playerSpeed));
            break;
        default:
            break;
    }
}