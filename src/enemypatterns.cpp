#include "enemypatterns.hpp"

namespace BBong {
HorizonPattern::HorizonPattern(float s) { speed = s; }

glm::vec3 HorizonPattern::move(glm::vec3 origin, float time) {
  if (origin.x < GameConfig::POSITION_LEFT_LIMIT ||
      origin.x > GameConfig::POSITION_RIGHT_LIMIT)
    direction.x = -direction.x;
  return origin + Utility::getNormalizedDirection(direction, time * speed);
}
} // namespace MovementPattern

namespace BBong {
// ===================== CirclePattern =====================
CirclePattern::CirclePattern(float s, int num) : numBullets(num) { speed = s; }

std::vector<std::function<glm::vec3(glm::vec3, float)>> CirclePattern::fire() {
  std::vector<std::function<glm::vec3(glm::vec3, float)>> actions;
  actions.reserve(numBullets);

  float angleStep = 2 * glm::pi<float>() / numBullets;
  float angle = (maxFireCount / 2 > fireCount) ? 0.0f : angleStep / 2;
  for (int i = 0; i < numBullets; i++) {
    angle += angleStep;
    glm::vec3 dir(cos(angle), sin(angle), 0.0f);
    actions.push_back(straight(dir, this->speed));
  }

  return actions;
}

// ===================== SpiralPattern =====================
SpiralPattern::SpiralPattern(float s, float step)
    : angle(-90.0f), angleStep(step) {
  speed = s;
}

std::vector<std::function<glm::vec3(glm::vec3, float)>> SpiralPattern::fire() {
  std::vector<std::function<glm::vec3(glm::vec3, float)>> actions;

  glm::vec3 dir(cos(angle), sin(angle), 0.0f);
  actions.push_back(straight(dir, speed));

  angle += angleStep;
  return actions;
}

// ===================== RandomBurstPattern =====================
RandomBurstPattern::RandomBurstPattern(float s, int c)
    : count(c), rng(std::random_device{}()), dist(0.0f, 2 * glm::pi<float>()) {
  speed = s;
}

std::vector<std::function<glm::vec3(glm::vec3, float)>>
RandomBurstPattern::fire() {
  std::vector<std::function<glm::vec3(glm::vec3, float)>> actions;
  actions.reserve(count);

  for (int i = 0; i < count; i++) {
    float angle = dist(rng);
    glm::vec3 dir(cos(angle), sin(angle), 0.0f);
    actions.push_back(straight(dir, speed));
  }

  return actions;
}
} // namespace ShootingPattern