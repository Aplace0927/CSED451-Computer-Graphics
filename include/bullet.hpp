#ifndef BULLET_HPP
#define BULLET_HPP

#include "object.hpp"
#include "utils.hpp"
#include <functional>
#include <chrono>

namespace Bullet {
    enum class BulletType {
        PLAYER,
        ENEMY,
        NONE
    };

    class Bullet : public Object::Object<glm::vec3, Shape::RGBColor> {
    public:
        Bullet();
        void update(time_t time) override;
        void fixedUpdate() override;
        void deactivate();
        void activate(
            glm::vec3 bullet_origin,
            std::function<glm::vec3(glm::vec3, time_t)> movement_pattern,
            BulletType bullet_shooter
        );
        void draw(time_t current_time);

    private:
        BulletType bullet_shooter;
        time_t created_time;
        glm::vec3 bullet_origin;
        std::function<glm::vec3(glm::vec3, time_t)> movement_pattern;
    };
}

namespace BulletPattern {
    constexpr float BulletSpeed = 0.001f;
    namespace Player {
        inline std::function<glm::vec3(glm::vec3, time_t)> straight_up() {
            return [](glm::vec3 origin, time_t time_elapsed) {
                float linear_speed = BulletSpeed * static_cast<float>(time_elapsed);
                return origin + glm::vec3(0.0f, linear_speed, 0.0f);
            };
        }
    }

    namespace Enemy {
        inline std::function<glm::vec3(glm::vec3, time_t)> straight(glm::vec3 direction) {
            return [direction](glm::vec3 origin, time_t time_elapsed) {
                float linear_speed = BulletSpeed * static_cast<float>(time_elapsed);
                return origin + Utils::getNormalizedDirection(direction);
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

    inline std::function<glm::vec3(glm::vec3, time_t)> empty() {
        return [](glm::vec3 origin, time_t time_elapsed) {
            return origin;
        };
    }
}

#endif // BULLET_HPP