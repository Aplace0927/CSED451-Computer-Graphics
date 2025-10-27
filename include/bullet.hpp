#ifndef BULLET_HPP 
#define BULLET_HPP

#include <functional>
#include <iostream>
#include <memory>
#include <glm/glm.hpp>

#include "BBong/component.hpp"
#include "utility.hpp"

namespace BBong {

enum class BulletType { PLAYER, ENEMY, NONE };

class Bullet : public ClonableComponent<Bullet> {
public:
  explicit Bullet(GameObject *owner) : ClonableComponent(owner) {}

  void update() override;
  void fixedUpdate() override;

private:
  bool isInRenderBounds(const glm::vec3 &pos);

  BulletType bullet_shooter;
  glm::vec3 bullet_origin = glm::vec3(0.0f);
  std::function<glm::vec3(glm::vec3, float)> movement_pattern;
};

class PlayerBullet : public Bullet {
public:
  explicit PlayerBullet(GameObject *owner) : Bullet(owner) {}
};

class EnemyBullet : public Bullet {
public:
  explicit EnemyBullet(GameObject *owner) : Bullet(owner) {}
};

constexpr float BulletSpeed = 100.0f;

inline std::function<glm::vec3(glm::vec3, float)>
straight(glm::vec3 direction, float speed = BulletSpeed) {
  return [direction, speed](glm::vec3 origin, float time_elapsed) {
    return origin +
           Utility::getNormalizedDirection(direction, speed * time_elapsed);
  };
}

inline std::function<glm::vec3(glm::vec3, float)> empty() {
  return [](glm::vec3 origin, float time_elapsed) { return origin; };
}
} // namespace BBong

#endif // BULLET_HPP