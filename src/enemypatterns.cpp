#include "enemypatterns.hpp"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace enemypatterns {
    // ===================== CirclePattern =====================
    CirclePattern::CirclePattern(int n, float s) : numBullets(n), speed(s) {}

    void CirclePattern::update(float bossX, float bossY, float time,
        std::vector<Bullet::Bullet>& bullets) {
        for (int i = 0; i < numBullets; i++) {
            float angle = 2 * M_PI * i / numBullets;
            float vx = cos(angle) * speed;
            float vy = sin(angle) * speed;
            bullets.emplace_back(bossX, bossY, vx, vy);
        }
    }

    // ===================== SpiralPattern =====================
    SpiralPattern::SpiralPattern(float s, float step) : speed(s), angle(0), angleStep(step) {}

    void SpiralPattern::update(float bossX, float bossY, float time,
        std::vector<Bullet::Bullet>& bullets) {
        angle += angleStep;
        float vx = cos(angle) * speed;
        float vy = sin(angle) * speed;
        bullets.emplace_back(bossX, bossY, vx, vy);
    }

    // ===================== WavePattern =====================
    WavePattern::WavePattern(float s, float f, float a) : speed(s), freq(f), amp(a) {}

    void WavePattern::update(float bossX, float bossY, float time,
        std::vector<Bullet::Bullet>& bullets) {
        float vx = sin(time * freq) * amp;
        float vy = speed;
        bullets.emplace_back(bossX, bossY, vx, vy);
    }

    // ===================== RandomBurstPattern =====================
    RandomBurstPattern::RandomBurstPattern(float s, int c) : speed(s), count(c) {}

    void RandomBurstPattern::update(float bossX, float bossY, float time,
        std::vector<Bullet::Bullet>& bullets) {
        for (int i = 0; i < count; i++) {
            float angle = ((float)rand() / RAND_MAX) * 2 * M_PI;
            float vx = cos(angle) * speed;
            float vy = sin(angle) * speed;
            bullets.emplace_back(bossX, bossY, vx, vy);
        }
    }

} // namespace enemypatterns
