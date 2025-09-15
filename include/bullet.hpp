#ifndef BULLET_HPP
#define BULLET_HPP

#include "object.hpp"
#include <functional>
#include <chrono>

namespace Bullet {
    enum class BulletType {
        PLAYER,
        ENEMY
    };

    class Bullet : public Object::Object<glm::vec3, Shape::RGBColor> {
    public:
        Bullet(
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
    constexpr float BulletSpeed = 0.000005f;
    inline std::function<glm::vec3(glm::vec3, time_t)> straight_down() {
        return [](glm::vec3 origin, time_t time_elapsed) {
            return origin + glm::vec3(0.0f, -BulletSpeed * static_cast<float>(time_elapsed), 0.0f);
        };
    }
}

#endif // BULLET_HPP