#include "enemypatterns.hpp"
#include <iostream>

namespace ShootingPattern {
    // ===================== CirclePattern =====================
    CirclePattern::CirclePattern(int num) : numBullets(num) {}

    std::vector<std::function<glm::vec3(glm::vec3, time_t)>> CirclePattern::fire() {
        std::vector<std::function<glm::vec3(glm::vec3, time_t)>> actions;
        actions.reserve(numBullets);

        float angleStep = 2 * glm::pi<float>() / numBullets;
        float angle = (maxFireCount / 2 > fireCount) ? 0.0f : angleStep / 2;
        for (int i = 0; i < numBullets; i++) {
            angle += angleStep;
            glm::vec3 dir(cos(angle), sin(angle), 0.0f);
            actions.push_back(BulletPattern::Enemy::straight(dir, this->speed));
        }

        return actions;
    }

    // ===================== SpiralPattern =====================
    SpiralPattern::SpiralPattern(float s, float step) : speed(s), angle(0), angleStep(step) {}

    std::vector<std::function<glm::vec3(glm::vec3, time_t)>> SpiralPattern::fire() {
        return std::vector<std::function<glm::vec3(glm::vec3, time_t)>>();
    }

    // ===================== WavePattern =====================
    WavePattern::WavePattern(float s, float f, float a) : speed(s), freq(f), amp(a) {}

    std::vector<std::function<glm::vec3(glm::vec3, time_t)>> WavePattern::fire() {
        return std::vector<std::function<glm::vec3(glm::vec3, time_t)>>();
    }

    // ===================== RandomBurstPattern =====================
    RandomBurstPattern::RandomBurstPattern(float s, int c) : speed(s), count(c) {}

    std::vector<std::function<glm::vec3(glm::vec3, time_t)>> RandomBurstPattern::fire() {
        return std::vector<std::function<glm::vec3(glm::vec3, time_t)>>();
    }

} // namespace enemypatterns