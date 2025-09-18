#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <cmath>

#include "object.hpp"
#include "objectpool.hpp"
#include "bullet.hpp"
#include "healthbar.hpp"

namespace Enemy {
    class Enemy : public Object::Object<glm::vec3, Shape::RGBColor> {
    public:
        Enemy();
        void update(time_t time) override;
        void fixedUpdate() override;

        std::function<void()> getBulletHitDetectHandlerFunction() {
            return [this]() {
                enemyHealth = glm::max(0, enemyHealth - 1);
                healthBar.setCurrentHealth(enemyHealth);
                if (enemyHealth == 0) {
                    setStatus(false);
                    healthBar.setStatus(false);
                }
            };
        }
        
    private:
        // Add enemy state variables here 
        int enemyHealth;
        ObjectPool::ObjectPool<Bullet::Bullet> bullets;
        HealthBar::HealthBar healthBar;
    };
};
#endif // ENEMY_HPP