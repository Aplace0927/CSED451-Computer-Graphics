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
        virtual ~IPattern() = default;
        virtual void fire(glm::vec3 center, ObjectPool::ObjectPool<Bullet::Bullet> bulletPool) = 0;
    };

    class CirclePattern : public IPattern {
        int numBullets;
        float speed;
    public:
        CirclePattern(int n, float s);
        void fire(glm::vec3 center, ObjectPool::ObjectPool<Bullet::Bullet> bulletPool) override;
    };

    class SpiralPattern : public IPattern {
        float speed;
        float angle;
        float angleStep;
    public:
        SpiralPattern(float s, float step);
        void fire(glm::vec3 center, ObjectPool::ObjectPool<Bullet::Bullet> bulletPool) override;
    };

    class WavePattern : public IPattern {
        float speed;
        float freq;
        float amp;
    public:
        WavePattern(float s, float f, float a);
        void fire(glm::vec3 center, ObjectPool::ObjectPool<Bullet::Bullet> bulletPool) override;
    };

    class RandomBurstPattern : public IPattern {
        float speed;
        int count;
    public:
        RandomBurstPattern(float s, int c);
        void fire(glm::vec3 center, ObjectPool::ObjectPool<Bullet::Bullet> bulletPool) override;
    };
}

#endif // ENEMYPATTERNS_HPP