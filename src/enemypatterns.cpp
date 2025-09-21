#include "enemypatterns.hpp"
#include <iostream>

namespace enemypatterns {
    // ===================== CirclePattern =====================
    CirclePattern::CirclePattern(int num, float speed) : numBullets(num), speed(speed) {}

    void CirclePattern::fire(glm::vec3 center, ObjectPool::ObjectPool<Bullet::Bullet> bulletPool) {
        float angle = 2 * glm::pi<float>() / numBullets;
        for (int i = 0; i < numBullets; i++) {
            Bullet::Bullet* newBullet = bulletPool.acquire();
            newBullet->activate(
                center,
                BulletPattern::Enemy::straight(glm::vec3(cos(angle*i), sin(angle*i), 0), speed),
                Bullet::BulletType::ENEMY,
                [&bulletPool, newBullet]() { bulletPool.release(newBullet); }
            );
        }
    }

    // ===================== SpiralPattern =====================
    SpiralPattern::SpiralPattern(float s, float step) : speed(s), angle(0), angleStep(step) {}

    void SpiralPattern::fire(glm::vec3 center, ObjectPool::ObjectPool<Bullet::Bullet> bulletPool) {
    }

    // ===================== WavePattern =====================
    WavePattern::WavePattern(float s, float f, float a) : speed(s), freq(f), amp(a) {}

    void WavePattern::fire(glm::vec3 center, ObjectPool::ObjectPool<Bullet::Bullet> bulletPool) {
    }

    // ===================== RandomBurstPattern =====================
    RandomBurstPattern::RandomBurstPattern(float s, int c) : speed(s), count(c) {}

    void RandomBurstPattern::fire(glm::vec3 center, ObjectPool::ObjectPool<Bullet::Bullet> bulletPool) {
    }

} // namespace enemypatterns