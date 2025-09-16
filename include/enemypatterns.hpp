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
        virtual void update(float bossX, float bossY, float time,
            std::vector<Bullet::Bullet>& bullets) = 0;
    };

    class CirclePattern : public IPattern {
        int numBullets;
        float speed;
    public:
        CirclePattern(int n, float s);
        void update(float bossX, float bossY, float time,
            std::vector<Bullet::Bullet>& bullets) override;
    };

    class SpiralPattern : public IPattern {
        float speed;
        float angle;
        float angleStep;
    public:
        SpiralPattern(float s, float step);
        void update(float bossX, float bossY, float time,
            std::vector<Bullet::Bullet>& bullets) override;
    };

    class WavePattern : public IPattern {
        float speed;
        float freq;
        float amp;
    public:
        WavePattern(float s, float f, float a);
        void update(float bossX, float bossY, float time,
            std::vector<Bullet::Bullet>& bullets) override;
    };

    class RandomBurstPattern : public IPattern {
        float speed;
        int count;
    public:
        RandomBurstPattern(float s, int c);
        void update(float bossX, float bossY, float time,
            std::vector<Bullet::Bullet>& bullets) override;
    };
}

#endif // ENEMYPATTERNS_HPP