#include "enemy.hpp"

namespace BBong {
//void Enemy::update() {
//  if (gameState == GameState::WIN) {
//    this->setActive(false);
//    //healthBar.setActive(false);
//    return;
//  }
//
//  if (getStatus()) {
//    draw(Utility::getCurrentTimeMS());
//  }
//  return;
//}
//
//void Enemy::fixedUpdate() {
//  if (!getStatus()) {
//    return;
//  }
//  updateMovementPattern();
//  updateShootingPattern();
//}
//
//void Enemy::updateMovementPattern() {
//  if (!movementPattern)
//    return;
//  setPosition(movementPattern->move(getCenter(), GameConfig::FIXED_DELTATIME));
//}
//
//void Enemy::updateShootingPattern() {
//  if (!shootingPattern)
//    return;
//
//  if (shootingPattern->fireCount <= 0) {
//    shootingPattern = chooseShootingPattern();
//    shootingPattern->Init();
//  } else {
//    shootingPattern->timeSinceLastFire += GameConfig::FIXED_DELTATIME;
//    if (shootingPattern->timeSinceLastFire > shootingPattern->cooldown) {
//      shooting();
//      shootingPattern->fireCount--;
//    }
//  }
//}
//
//ShootingPattern *chooseShootingPattern() {
//  static std::mt19937 rng(std::random_device{}());
//  std::uniform_int_distribution<int> dist(0, 2);
//
//  return shootingPatterns[dist(rng)];
//}
//
//void Enemy::shooting() {
//  for (const std::function<glm::vec3(glm::vec3, float)> &func :
//       shootingPattern->fire()) {
//    Bullet::EnemyBullet *newBullet = bullets.acquire();
//    newBullet->activate(
//        getCenter(), func, Bullet::BulletType::ENEMY,
//        [this, newBullet]() { this->bullets.release(newBullet); },
//        bulletHitDetectFunction, bulletHitEventFunction);
//  }
//}
} // namespace Enemy