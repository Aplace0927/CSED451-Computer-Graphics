#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <cmath>

#include "object.hpp"

namespace Enemy {
    class Enemy : public Object::Object<glm::vec3, Shape::RGBColor> {
    public:
        Enemy();
    private:
        // Add enemy state variables here 
        int enemyHealth;
    };

    namespace BulletPattern {
        constexpr float BulletSpeed = 0.0001f;
        inline std::function<glm::vec3(glm::vec3, time_t)> straight_down() {
            return [](glm::vec3 origin, time_t time_elapsed) {
                float linear_speed = BulletSpeed * static_cast<float>(time_elapsed);
                return origin + glm::vec3(0.0f, -linear_speed, 0.0f);
            };
        }

        inline std::function<glm::vec3(glm::vec3, time_t)> circular_motion() {
            return [](glm::vec3 origin, time_t time_elapsed) {
                float linear_speed = BulletSpeed * static_cast<float>(time_elapsed);
                float angular_speed = time_elapsed * 0.005f; // 0.005 rad/ms = 5 rad/s
                return origin + glm::vec3(
                    std::cos(angular_speed + glm::radians(90.0f)) * 0.1f,
                    -linear_speed + std::sin(angular_speed) * 0.1f,
                    0.0f
                );
            };
        }
    }
};
#endif // ENEMY_HPP