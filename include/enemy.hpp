#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <cmath>

#include "object.hpp"
#include "objectpool.hpp"
#include "bullet.hpp"
#include "enemypatterns.hpp"
#include "healthbar.hpp"

namespace Enemy {
    class Enemy : public Object::Object<glm::vec3, Shape::RGBColor> {
    public:
        Enemy();
        void update(float time) override;
        void fixedUpdate() override;
        void setBulletHitDetectFunction(const std::function<bool(const BoundingBox::BoundingBox<glm::vec3>&)>& func) {
            bulletHitDetectFunction = func;
        }
        void setBulletHitEventFunction(const std::function<void()>& func) {
            bulletHitEventFunction = func;
        }


        std::function<void()> getBulletHitDetectHandlerFunction() {
            return [this]() {
                enemyHealth = glm::max(0, enemyHealth - 1);
                healthBar.setCurrentHealth(enemyHealth);
                if (enemyHealth == 0) {
                    this->setStatus(false);
                    healthBar.setStatus(false);
                }
            };
        }
        
    private:
        int enemyHealth;
        ObjectPool::ObjectPool<Bullet::Bullet> bullets;
        HealthBar::HealthBar healthBar;
        
        MovementPattern::MovementPattern* movementPattern;
        ShootingPattern::ShootingPattern* shootingPattern;
        time_t movingCooldown;
        time_t shootingCooldown;

        std::function<bool(const BoundingBox::BoundingBox<glm::vec3>&)> bulletHitDetectFunction;
        std::function<void()> bulletHitEventFunction;
		
		void updateMovementPattern();
		void updateShootingPattern();
        ShootingPattern::ShootingPattern* chooseShootingPattern();
        void shooting();
    };
};
#endif // ENEMY_HPP