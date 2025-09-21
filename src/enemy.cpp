#include "enemy.hpp"

Enemy::Enemy::Enemy()
    : Object::Object(
        // Center at origin
        glm::vec3(0.0f, +0.5f, 0.0f), 
        Shape::Shape<glm::vec3, Shape::RGBColor>(    
            // subshapes: vector of subshapes, each subshape is a vector of vertices
            std::vector<std::vector<glm::vec3>>{
                {
                    glm::vec3(-0.1f, 0.0f, 0.0f),
                    glm::vec3(-0.05f, 0.05f, 0.0f),
                    glm::vec3( 0.05f, 0.05f, 0.0f),
                    glm::vec3( 0.1f, 0.0f, 0.0f),
                    glm::vec3( 0.05f, -0.05f, 0.0f),
                    glm::vec3(-0.05f, -0.05f, 0.0f),
                    glm::vec3(-0.1f, 0.0f, 0.0f),
                }
            },
            // colors: vector of color sets, each set is a vector of colors for the subshape
            std::vector<std::vector<Shape::RGBColor>>{
                {
                    Shape::RGBColor(1.0f, 0.0f, 0.0f),
                    Shape::RGBColor(1.0f, 0.0f, 0.0f),
                    Shape::RGBColor(1.0f, 0.0f, 0.0f),
                    Shape::RGBColor(1.0f, 0.0f, 0.0f),
                    Shape::RGBColor(1.0f, 0.0f, 0.0f),
                    Shape::RGBColor(1.0f, 0.0f, 0.0f),
                    Shape::RGBColor(1.0f, 0.0f, 0.0f),
                }
            },
            // drawMethod: vector of draw methods for each subshape
            std::vector<unsigned int>{ GL_TRIANGLE_FAN }
        )
    ),
    enemyHealth(100),
    healthBar(
        glm::vec3(GameConfig::ENEMY_DIGIT_X, GameConfig::ENEMY_DIGIT_Y, 0.0f),
        GameConfig::FONT_DIGIT_SIZE,
        glm::vec3(GameConfig::ENEMY_GAUGE_X, GameConfig::ENEMY_GAUGE_Y, 0.0f),
        GameConfig::ENEMY_GAUGE_WIDTH,
        GameConfig::ENEMY_GAUGE_HEIGHT,
        enemyHealth
    )
{
    bullets = ObjectPool::ObjectPool<Bullet::Bullet>();
    // Initialize other enemy state variables here if needed
}

void Enemy::Enemy::update(time_t time) {
    /**
     * if (time - patternRefreshTime >= GameConfig::ENEMY_PATTERN_REFRESH_INTERVAL) {
     *    // Update movement (and shooting) patterns - could be seperated
     *    // Pattern update time also could be changed
     * }
     * 
     */
    // if (!time - shootingCooldown >= GameConfig::ENEMY_SHOOTING_COOLDOWN_MS) {
    //     Bullet::Bullet* newBullet = bullets.acquire();
    //     newBullet->activate(
    //         getCenter() + glm::vec3(0.0f, -0.05f, 0.0f),
    //         shootingPattern.shoot(getCenter(), time - patternRefreshTime),
    //         Bullet::BulletType::ENEMY,
    //         [this, newBullet]() { this->bullets.release(newBullet); },
    //         bulletHitDetectFunction,
    //         bulletHitEventFunction
    //     );
    //     shootingCooldown = time;
    // }

    if (!getStatus()) {
        return;
    }
    draw();
    return;
    // Implement enemy behavior here
}

void Enemy::Enemy::fixedUpdate() {
    if (!getStatus()) {
        return;
    }
    // move(movementPattern.move());
}