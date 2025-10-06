#include "enemy.hpp"

namespace Enemy {
Enemy::Enemy()
    : Object::Object(
      SceneGraph::createEnemy()
    ),
      enemyHealth(GameConfig::ENEMY_LIFE)
      // healthBar(
      //     glm::vec3(GameConfig::ENEMY_DIGIT_X, GameConfig::ENEMY_DIGIT_Y, 0.0f),
      //     GameConfig::FONT_DIGIT_SIZE,
      //     glm::vec3(GameConfig::ENEMY_GAUGE_X, GameConfig::ENEMY_GAUGE_Y, 0.0f),
      //     GameConfig::ENEMY_GAUGE_WIDTH, GameConfig::ENEMY_GAUGE_HEIGHT,
      //     enemyHealth)
          {
  bullets = ObjectPool::ObjectPool<Bullet::EnemyBullet>();
  shootingPatterns = {new ShootingPattern::CirclePattern(200.0f, 12),
                      new ShootingPattern::SpiralPattern(200.0f, 20.0f),
                      new ShootingPattern::RandomBurstPattern(250.0f, 5)};
  shootingPattern = chooseShootingPattern();
  movementPattern = new MovementPattern::HorizonPattern(100.0f);
}

void Enemy::update(float time) {
  if (gameState == GameState::GameState::WIN) {
    this->setStatus(false);
    //healthBar.setStatus(false);
    return;
  }

  if (getStatus()) {
    draw(Utility::getCurrentTimeMS());
  }
  return;
}

void Enemy::fixedUpdate() {
  if (!getStatus()) {
    return;
  }
  updateMovementPattern();
  updateShootingPattern();
}

void Enemy::updateMovementPattern() {
  if (!movementPattern)
    return;
  setPosition(movementPattern->move(getCenter(), GameConfig::FIXED_DELTATIME));
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

ShootingPattern::ShootingPattern *Enemy::chooseShootingPattern() {
  static std::mt19937 rng(std::random_device{}());
  std::uniform_int_distribution<int> dist(0, 2);

  return shootingPatterns[dist(rng)];
}

void Enemy::shooting() {
  for (const std::function<glm::vec3(glm::vec3, float)> &func :
       shootingPattern->fire()) {
    Bullet::EnemyBullet *newBullet = bullets.acquire();
    newBullet->activate(
        getCenter(), func, Bullet::BulletType::ENEMY,
        [this, newBullet]() { this->bullets.release(newBullet); },
        bulletHitDetectFunction, bulletHitEventFunction);
  }
}
} // namespace Enemy