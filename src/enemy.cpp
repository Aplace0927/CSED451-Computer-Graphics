#include "enemy.hpp"

namespace Enemy
{
    Enemy::Enemy() :
        Object::Object(
            glm::vec3(0.0f, GameConfig::WINDOW_HEIGHT / 4, 0.0f),
            Shape::Shape<glm::vec3, Shape::RGBColor>(
                std::vector<std::vector<glm::vec3>>{
                    {
                        glm::vec3(-40.0f, 0.0f, 0.0f),
                            glm::vec3(-20.0f, 34.6f, 0.0f),
                            glm::vec3(20.0f, 34.6f, 0.0f),
                            glm::vec3(40.0f, 0.0f, 0.0f),
                            glm::vec3(20.0f, -34.6f, 0.0f),
                            glm::vec3(-20.0f, -34.6f, 0.0f),
                            glm::vec3(-40.0f, 0.0f, 0.0f),
                    }
    },
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
        shootingPattern = chooseShootingPattern();
        movementPattern = new MovementPattern::HorizonPattern(100.0f);
    }

    void Enemy::update(float time) {
        if (!getStatus()) {
            return;
        }
        draw();
    }

    void Enemy::fixedUpdate() {
        if (!getStatus()) {
            return;
        }
        updateMovementPattern();
        updateShootingPattern();
    }

    void Enemy::updateMovementPattern() {
        if (!movementPattern)
            return;
        setPosition(movementPattern->move(getCenter(), GameConfig::FIXED_DELTATIME));
    }

    void Enemy::updateShootingPattern() {
        if (!shootingPattern)
            return;

        if (shootingPattern->fireCount <= 0)
        {
            delete shootingPattern;
            shootingPattern = chooseShootingPattern();
        }
        else
        {
            shootingPattern->timeSinceLastFire += GameConfig::FIXED_DELTATIME;
            if (shootingPattern->timeSinceLastFire > shootingPattern->cooldown) {
                shooting();
                shootingPattern->fireCount--;
            }
        }
    }

    ShootingPattern::ShootingPattern* Enemy::chooseShootingPattern()
    {
        static std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> dist(1, 3);

        switch (dist(rng))
        {
        case 1:
            return new ShootingPattern::CirclePattern(500.0f, 6);
        case 2:
            return new ShootingPattern::SpiralPattern(400.0f, glm::radians(10.0f));
        case 3:
            return new ShootingPattern::RandomBurstPattern(300.0f, 5);
        default:
            throw std::runtime_error("Invalid shooting pattern choice");
        };
    }

    void Enemy::shooting() {
        for (const std::function<glm::vec3(glm::vec3, float)>& func : shootingPattern->fire())
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
} // namespace Enemy