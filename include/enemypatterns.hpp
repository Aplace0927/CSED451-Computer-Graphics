#ifndef ENEMYPATTERNS_HPP
#define ENEMYPATTERNS_HPP

#include <vector>
#include <memory>
#include <cmath>
#include <cstdlib>
#include "bullet.hpp"
#include "objectpool.hpp"

namespace MovementPattern {
    class IMovementPattern {
    public:
        float speed = 0.001f;
        virtual ~IMovementPattern() = default;
        virtual std::vector<std::function<glm::vec3(glm::vec3, time_t)>> move() = 0;
    };

    class HorizonPattern : public IMovementPattern {
        int numBullets;
    public:
        HorizonPattern();
        std::vector<std::function<glm::vec3(glm::vec3, time_t)>> move() override;
    };
}

namespace ShootingPattern {
    class IShootingPattern {
    public:
        int fireCount = 10;
		int maxFireCount = 10;
		float cooldown = 0.2;
		float timeSinceLastFire = 0.0f;
		float speed = 0.001f;
        virtual ~IShootingPattern() = default;
        virtual std::vector<std::function<glm::vec3(glm::vec3, time_t)>> fire() = 0;
    };

    class CirclePattern : public IShootingPattern {
        int numBullets;
    public:
        CirclePattern(int num);
        std::vector<std::function<glm::vec3(glm::vec3, time_t)>> fire() override;
    };

    class SpiralPattern : public IShootingPattern {
        float speed;
        float angle;
        float angleStep;
    public:
        SpiralPattern(float s, float step);
        std::vector<std::function<glm::vec3(glm::vec3, time_t)>> fire() override;
    };

    class WavePattern : public IShootingPattern {
        float speed;
        float freq;
        float amp;
    public:
        WavePattern(float s, float f, float a);
        std::vector<std::function<glm::vec3(glm::vec3, time_t)>> fire() override;
    };

    class RandomBurstPattern : public IShootingPattern {
        float speed;
        int count;
    public:
        RandomBurstPattern(float s, int c);
        std::vector<std::function<glm::vec3(glm::vec3, time_t)>> fire() override;
    };
}

#endif // ENEMYPATTERNS_HPP