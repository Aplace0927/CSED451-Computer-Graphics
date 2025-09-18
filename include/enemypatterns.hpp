#ifndef ENEMYPATTERNS_HPP
#define ENEMYPATTERNS_HPP

#include <vector>
#include <memory>
#include <cmath>
#include <cstdlib>
#include "bullet.hpp"

namespace enemypatterns {
    class IPattern {
    public:
        virtual ~IPattern() = default;
        virtual void update(glm::vec3 pos);
    };

    class CirclePattern : public IPattern {
        int numBullets;
        float speed;
    public:
        CirclePattern(int n, float s);
        void update(glm::vec3 pos) override;
    };

    class SpiralPattern : public IPattern {
        float speed;
        float angle;
        float angleStep;
    public:
        SpiralPattern(float s, float step);
        void update(glm::vec3 pos) override;
    };

    class WavePattern : public IPattern {
        float speed;
        float freq;
        float amp;
    public:
        WavePattern(float s, float f, float a);
        void update(glm::vec3 pos) override;
    };

    class RandomBurstPattern : public IPattern {
        float speed;
        int count;
    public:
        RandomBurstPattern(float s, int c);
        void update(glm::vec3 pos) override;
    };
}

#endif // ENEMYPATTERNS_HPP