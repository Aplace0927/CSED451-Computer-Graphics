#include "enemy.hpp"
#include <iostream>

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
    enemyHealth(GameConfig::ENEMY_LIFE),
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
    shootingPattern = new ShootingPattern::CirclePattern(10);
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
}

void Enemy::Enemy::fixedUpdate() {
    updateMovementPattern();
	updateShootingPattern();
}

void Enemy::Enemy::updateMovementPattern() {
    if (!movementPattern)
        return;
}

void Enemy::Enemy::updateShootingPattern() {
    if (!shootingPattern)
        return;

    if (shootingPattern->fireCount <= 0)
    {
        delete shootingPattern;
        shootingPattern = new ShootingPattern::CirclePattern(10);
    }
    else
    {
        shootingPattern->timeSinceLastFire += GameConfig::FIXED_DELTATIME;
        if (shootingPattern->timeSinceLastFire > shootingPattern->cooldown) {
            attack();
            shootingPattern->fireCount--;
        }
    }

}

void Enemy::Enemy::attack() {
    for (const std::function<glm::vec3(glm::vec3, time_t)> &func : shootingPattern->fire())
    {
        Bullet::Bullet* newBullet = bullets.acquire();
        newBullet->activate(
            getCenter(),
            func,
            Bullet::BulletType::ENEMY,
            [this, newBullet]() { this->bullets.release(newBullet); },
            bulletHitDetectFunction,
            bulletHitEventFunction
        );
    }
}