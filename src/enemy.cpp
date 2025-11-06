#include "enemy.hpp"

namespace BBong {
void Enemy::fixedUpdate() {
  updateMovementPattern();
  updateShootingPattern();
}

void Enemy::updateMovementPattern() {
  if (!movementPattern)
    return;
  transform->setPosition(
      movementPattern->move(transform->position, GameConfig::FIXED_DELTATIME));
}

void Enemy::updateShootingPattern() {
  if (!shootingPattern)
    return;

  if (shootingPattern->fireCount <= 0) {
    shootingPattern = chooseShootingPattern();
    shootingPattern->Init();
  } else {
    shootingPattern->timeSinceLastFire += GameConfig::FIXED_DELTATIME;
    if (shootingPattern->timeSinceLastFire > shootingPattern->cooldown) {
      shooting();
      shootingPattern->fireCount--;
    }
  }
}

ShootingPattern *Enemy::chooseShootingPattern() {
  static std::mt19937 rng(std::random_device{}());
  std::uniform_int_distribution<int> dist(0, 2);
  return shootingPatterns[dist(rng)];
}

void Enemy::shooting() {
  for (const std::function<glm::vec3(glm::vec3, float)> &func :
       shootingPattern->fire()) {

    auto *newBullet = bullets->acquire();
    newBullet->transform->setPosition(transform->position);
  }
}
} // namespace BBong