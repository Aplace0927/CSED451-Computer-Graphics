#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "object.hpp"
#include "objectpool.hpp"
#include "bullet.hpp"

namespace Player {
    class Player : public Object::Object<glm::vec3, Shape::RGBColor> {
    public:
        Player();
        void update(time_t time) override;
		// void fixedUpdate() override;
        void setDirection(const glm::vec3& input) {
            direction = input;
		}
        void shooting(bool shooting) {
            isShooting = shooting;
            if (!isShooting) {
                shootingCooldown = 0;
            }
        }
    private:
        // Add player state variables here 
        int playerHealth;
        bool isShooting;
        time_t shootingCooldown;
		glm::vec3 direction;
        ObjectPool::ObjectPool<Bullet::Bullet> bullets;
    };
};
#endif // PLAYER_HPP