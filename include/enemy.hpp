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
        void update(time_t time) override;
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
                    setStatus(false);
                    healthBar.setStatus(false);
                }
            };
        }
        
    private:
        int enemyHealth;
        enemypatterns::IPattern* currentPattern;
        ObjectPool::ObjectPool<Bullet::Bullet> bullets;
        HealthBar::HealthBar healthBar;
        std::function<bool(const BoundingBox::BoundingBox<glm::vec3>&)> bulletHitDetectFunction;
        std::function<void()> bulletHitEventFunction;
		void attack();
    };
};
#endif // ENEMY_HPP