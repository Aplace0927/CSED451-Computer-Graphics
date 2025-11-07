#include "enemy.hpp"

namespace BBong {
void Enemy::fixedUpdate() {
  updateMovementPattern();
  updateShootingPattern();
}

void Enemy::collision3D(Collider3D *collider) {
  enemyHealth--;
  if (enemyHealth < 0) {
    Game::getInstance().mainScene->destroyGameObject(gameObject);
  }
}

void Enemy::updateMovementPattern() {
  for each (auto movementPattern in movementPatterns) {
    if (!movementPattern)
      return;
    transform->setWorldPosition(movementPattern->move(
        transform->getWorldPosition(), GameConfig::FIXED_DELTATIME));
  }
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
    newBullet->transform->setWorldPosition(transform->getWorldPosition());
    
    glm::vec3 dir = Utility::getNormalizedDirection(func(glm::vec3(0.0f), 1.0f));
    dir.z = Utility::randFloatRange(-0.2f, 0.2f);

    // setMoveDirection is method of Bullet, so cast to getComponent<Bullet>()
    newBullet->getComponent<Bullet>()->setMoveDirection(
      dir
    );
  }
}
} // namespace BBong