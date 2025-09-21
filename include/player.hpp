#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "object.hpp"
#include "config.hpp"
#include "objectpool.hpp"
#include "bullet.hpp"
#include "healthbar.hpp"

namespace Player {
    class Player : public Object::Object<glm::vec3, Shape::RGBColor> {
    public:
        Player();
        void update(time_t time) override;
		void fixedUpdate() override;
        void setDirection(const glm::vec3& input) {
            direction = input;
		}
        void shooting(bool shooting) {
            isShooting = shooting;
            if (!isShooting) {
                shootingCooldown = 0;
            }
        }

        void setBulletHitDetectFunction(const std::function<bool(const BoundingBox::BoundingBox<glm::vec3>&)> &func) {
            bulletHitDetectFunction = func;
        }
        void setBulletHitEventFunction(const std::function<void()> &func) {
            bulletHitEventFunction = func;
        }
        
        std::function<void()> getBulletHitDetectHandlerFunction() {
            return [this]() {
                playerHealth = glm::max(0, playerHealth - 1);
                healthBar.setCurrentHealth(playerHealth);
                if (playerHealth == 0) {
                    this->setStatus(false);
                    healthBar.setStatus(false);
                }
            };
        }

    private:
        // Add player state variables here 
        int playerHealth;
        glm::vec3 direction;
        bool isShooting;
        time_t shootingCooldown;
        
		HealthBar::HealthBar healthBar;
        ObjectPool::ObjectPool<Bullet::Bullet> bullets;
        std::function<bool(const BoundingBox::BoundingBox<glm::vec3>&)> bulletHitDetectFunction;
        std::function<void()> bulletHitEventFunction;
    };
};
#endif // PLAYER_HPP