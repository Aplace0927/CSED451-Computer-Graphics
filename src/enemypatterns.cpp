/*
#include "enemypatterns.hpp"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace enemypatterns {
    // ===================== CirclePattern =====================
    CirclePattern::CirclePattern(int n, float s) : numBullets(n), speed(s) {}

    void CirclePattern::update(glm::vec3 center) {
        Bullet::Bullet* newBullet = bullets.acquire();
        newBullet->activate(
            center,
            BulletPattern::Enemy::straight_up(),
            Bullet::BulletType::ENEMY
        );

        for (int i = 0; i < numBullets; i++) {
            float angle = 2 * M_PI * i / numBullets;
            float vx = cos(angle) * speed;
            float vy = sin(angle) * speed;
        }
    }

    // ===================== SpiralPattern =====================
    SpiralPattern::SpiralPattern(float s, float step) : speed(s), angle(0), angleStep(step) {}

    void SpiralPattern::update(float bossX, float bossY) {
        angle += angleStep;
        float vx = cos(angle) * speed;
        float vy = sin(angle) * speed;
    }

    // ===================== WavePattern =====================
    WavePattern::WavePattern(float s, float f, float a) : speed(s), freq(f), amp(a) {}

    void WavePattern::update(float bossX, float bossY) {
        float vx = sin(time * freq) * amp;
    }

    // ===================== RandomBurstPattern =====================
    RandomBurstPattern::RandomBurstPattern(float s, int c) : speed(s), count(c) {}

    void RandomBurstPattern::update(float bossX, float bossY, float time) {
        for (int i = 0; i < count; i++) {
            float angle = ((float)rand() / RAND_MAX) * 2 * M_PI;
            float vx = cos(angle) * speed;
            float vy = sin(angle) * speed;
        }
    }

} // namespace enemypatterns
*/