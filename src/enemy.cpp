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
    enemyHealth(1000),
    healthBar(glm::vec3(-0.80f, 0.0f, 0.0f), enemyHealth)
{
    bullets = ObjectPool::ObjectPool<Bullet::Bullet>();
    currentPattern = new enemypatterns::CirclePattern(10);
}

void Enemy::Enemy::update(time_t time) {
    draw();
}

void Enemy::Enemy::fixedUpdate() {
    if (!currentPattern)
        return;

    if (currentPattern->fireCount <= 0)
    {
		// Reset pattern
		delete currentPattern;
		currentPattern = new enemypatterns::CirclePattern(10);
    }
    else
    {
        currentPattern->timeSinceLastFire += GameConfig::FIXED_DELTATIME;
        if (currentPattern->timeSinceLastFire > currentPattern->cooldown) {
            attack();
            currentPattern->fireCount--;
        }
    }
}

void Enemy::Enemy::attack() {
    for each(std::function<glm::vec3(glm::vec3, time_t)> func in currentPattern->fire())
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