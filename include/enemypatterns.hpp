#ifndef ENEMYPATTERNS_HPP
#define ENEMYPATTERNS_HPP

#include <vector>
#include <memory>
#include <cmath>
#include <cstdlib>
#include "bullet.hpp"
#include "objectpool.hpp"

namespace enemypatterns {
    class IPattern {
    public:
        int fireCount = 10;
		int maxFireCount = 10;
		float cooldown = 0.2;
		float timeSinceLastFire = 0.0f;
		float speed = 0.001f;
        virtual ~IPattern() = default;
        virtual std::vector<std::function<glm::vec3(glm::vec3, time_t)>> fire() = 0;
    };

    class CirclePattern : public IPattern {
        int numBullets;
    public:
        CirclePattern(int num);
        std::vector<std::function<glm::vec3(glm::vec3, time_t)>> fire() override;
    };

    class SpiralPattern : public IPattern {
        float speed;
        float angle;
        float angleStep;
    public:
        SpiralPattern(float s, float step);
        std::vector<std::function<glm::vec3(glm::vec3, time_t)>> fire() override;
    };

    class WavePattern : public IPattern {
        float speed;
        float freq;
        float amp;
    public:
        WavePattern(float s, float f, float a);
        std::vector<std::function<glm::vec3(glm::vec3, time_t)>> fire() override;
    };

    class RandomBurstPattern : public IPattern {
        float speed;
        int count;
    public:
        RandomBurstPattern(float s, int c);
        std::vector<std::function<glm::vec3(glm::vec3, time_t)>> fire() override;
    };
}

#endif // ENEMYPATTERNS_HPP