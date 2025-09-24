#ifndef BULLET_HPP
#define BULLET_HPP

#include "object.hpp"
#include "utility.hpp"
#include <functional>
#include <iostream>

namespace Bullet {
    enum class BulletType {
        PLAYER,
        ENEMY,
        NONE
    };

    class Bullet : public Object::Object<glm::vec3, Shape::RGBColor> {
    public:
        Bullet(Shape::RGBColor color);
        void update(float time) override;
        void fixedUpdate() override;
        void deactivate();
        void activate(
            glm::vec3 bullet_origin,
            std::function<glm::vec3(glm::vec3, float)> movement_pattern,
            BulletType bullet_shooter,
            std::function<void()> releaseFunc = nullptr,
            std::function<bool(const BoundingBox::BoundingBox<glm::vec3>&)> hitDetectFunc = nullptr,
            std::function<void()> hitEventFunc = nullptr
        );

    private:
        bool isInRenderBounds(const glm::vec3& pos);

        BulletType bullet_shooter;
        glm::vec3 bullet_origin;
        std::function<glm::vec3(glm::vec3, float)> movement_pattern;
        std::function<bool(const BoundingBox::BoundingBox<glm::vec3>&)> hitDetectFunction;
        std::function<void()> hitEventFunction;
    };

    class PlayerBullet : public Bullet {
    public:
        PlayerBullet();
    };

    class EnemyBullet : public Bullet {
    public:
        EnemyBullet();
    };
}

namespace BulletPattern {
    constexpr float BulletSpeed = 100.0f;
    inline std::function<glm::vec3(glm::vec3, float)> straight(glm::vec3 direction, float speed = BulletSpeed) {
        return [direction, speed](glm::vec3 origin, float time_elapsed) {
            return origin + Utility::getNormalizedDirection(direction, speed * time_elapsed);
            };
    }

    inline std::function<glm::vec3(glm::vec3, float)> empty() {
        return [](glm::vec3 origin, float time_elapsed) {
            return origin;
            };
    }
}

#endif // BULLET_HPP