#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <cmath>

#include "object.hpp"
#include "objectpool.hpp"
#include "bullet.hpp"

namespace Enemy {
    class Enemy : public Object::Object<glm::vec3, Shape::RGBColor> {
    public:
        Enemy();
        void update(time_t time) override;
        void fixedUpdate() override;

        std::function<void()> getBulletHitDetectHandlerFunction() {
            return [this]() {
                enemyHealth = glm::max(0, enemyHealth - 1);
                printf("Enemy hit! Now health: %d\n", enemyHealth);
                if (enemyHealth == 0) {
                    Object::setStatus(false);
                }
            };
        }
        
    private:
        // Add enemy state variables here 
        int enemyHealth;
        ObjectPool::ObjectPool<Bullet::Bullet> bullets;
        
    };
};
#endif // ENEMY_HPP