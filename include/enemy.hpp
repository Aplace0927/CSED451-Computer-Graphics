#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <cmath>

#include "object.hpp"
#include "objectpool.hpp"
#include "bullet.hpp"
#include "enemypatterns.hpp"
//#include "healthbar.hpp"
#include "gamestate.hpp"

extern GameState::GameState gameState;

namespace Enemy {
class Enemy : public Object::Object<glm::vec3, Shape::RGBColor> {
public:
  Enemy();
  void update(float time) override;
  void fixedUpdate() override;
  void setBulletHitDetectFunction(
      const std::function<bool(const BoundingBox::BoundingBox<glm::vec3> &)>
          &func) {
    bulletHitDetectFunction = func;
  }
  void setBulletHitEventFunction(const std::function<void()> &func) {
    bulletHitEventFunction = func;
  }

  std::function<void()> getBulletHitDetectHandlerFunction() {
    return [this]() {
      if (!this->getStatus() || gameState != GameState::GameState::PLAYING) {
        return;
      }
      enemyHealth = glm::max(0, enemyHealth - 1);
      //healthBar.setCurrentHealth(enemyHealth);
      if (enemyHealth == 0) {
        gameState = GameState::GameState::WIN;
      }
    };
  }

private:
  int enemyHealth;
  ObjectPool::ObjectPool<Bullet::EnemyBullet> bullets;
  //HealthBar::HealthBar healthBar;

  MovementPattern::MovementPattern *movementPattern;
  ShootingPattern::ShootingPattern *shootingPattern;
  std::vector<ShootingPattern::ShootingPattern *> shootingPatterns;
  time_t movingCooldown;
  time_t shootingCooldown;

  std::function<bool(const BoundingBox::BoundingBox<glm::vec3> &)>
      bulletHitDetectFunction;
  std::function<void()> bulletHitEventFunction;

  void updateMovementPattern();
  void updateShootingPattern();
  ShootingPattern::ShootingPattern *chooseShootingPattern();
  void shooting();
};
}; // namespace Enemy
#endif // ENEMY_HPP