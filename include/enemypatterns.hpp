#ifndef ENEMYPATTERNS_HPP
#define ENEMYPATTERNS_HPP

#include <vector>
#include <memory>
#include <cmath>
#include <cstdlib>
#include <random>
#include "bullet.hpp"
#include "BBong/objectpool.hpp"

namespace BBong {
inline std::function<glm::vec3(glm::vec3, float)> straight(glm::vec3 direction,
                                                           float speed) {
  return [direction, speed](glm::vec3 origin, float time) -> glm::vec3 {
    return origin + (direction * speed * time);
  };
}

class MovementPattern {
protected:
  glm::vec3 direction = glm::vec3(1.0f, 0.0f, 0.0f);
  float speed = 10.0f;

public:
  virtual ~MovementPattern() = default;
  virtual glm::vec3 move(glm::vec3 origin, float time) = 0;
};

class HorizonPattern : public MovementPattern {
public:
  HorizonPattern(float s);
  glm::vec3 move(glm::vec3 origin, float time) override;
};

class ShootingPattern {
public:
  int fireCount = 10;
  int maxFireCount = 10;
  float cooldown = 0.2;
  float timeSinceLastFire = 0.0f;
  float speed = 1.0f;
  void Init() {
    fireCount = maxFireCount;
    timeSinceLastFire = cooldown;
  }
  virtual ~ShootingPattern() = default;
  virtual std::vector<std::function<glm::vec3(glm::vec3, float)>> fire() = 0;
};

class CirclePattern : public ShootingPattern {
  int numBullets;

public:
  CirclePattern(float s, int num);
  std::vector<std::function<glm::vec3(glm::vec3, float)>> fire() override;
};

class SpiralPattern : public ShootingPattern {
  float angle;
  float angleStep;

public:
  SpiralPattern(float s, float step);
  std::vector<std::function<glm::vec3(glm::vec3, float)>> fire() override;
};

class RandomBurstPattern : public ShootingPattern {
  int count;
  std::mt19937 rng;
  std::uniform_real_distribution<float> dist;

public:
  RandomBurstPattern(float s, int c);
  std::vector<std::function<glm::vec3(glm::vec3, float)>> fire() override;
};
} // namespace BBong

#endif // ENEMYPATTERNS_HPP