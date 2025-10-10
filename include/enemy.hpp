#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <cmath>

#include "object.hpp"
#include "objectpool.hpp"
#include "bullet.hpp"
#include "enemypatterns.hpp"
#include "healthbar.hpp"
#include "gamestate.hpp"

extern GameState::GameStateHolder gameState;

namespace Enemy {
class Enemy : public Object::Object<glm::vec3, Shape::RGBColor> {
public:
  Enemy(glm::vec3 origin, float speed);
  void update(float time) override;
  void fixedUpdate() override;

  void addBulletEventHandler(
      const std::pair<
        std::function<bool(const BoundingBox::BoundingBox<glm::vec3> &)>,
        std::function<void()>
      > &func) {
    hitEventHandlers.push_back(func);
  }

  std::function<void()> getBulletHitDetectHandlerFunction() {
    return [this]() {
      if (!this->getStatus() || gameState.currentState != GameState::GameState::PLAYING) {
        return;
      }
      this->enemyHealth = glm::max(0, this->enemyHealth - 1);

      // Update health bar
      getTransform()->getNthChild(0)->changeShape(HealthBar::generateHealthBar(
          glm::vec3(-30.0f, 60.0f, 0.0f), // digit position
          10.0f,                          // digit size
          glm::vec3(-40.0f, 40.0f, 0.0f), // gauge position
          80.0f,                          // gauge width
          10.0f,                          // gauge height
          this->enemyHealth,
          GameConfig::ENEMY_LIFE // max health
          ));
      if (this->enemyHealth == 0) {
        this->setStatus(false);
        if (--gameState.enemyLeft == 0) {
          gameState.currentState = GameState::GameState::WIN;
        }
      }
    };
  }

private:
  int enemyHealth;
  ObjectPool::ObjectPool<Bullet::EnemyBullet> bullets;
  // HealthBar::HealthBar healthBar;

  ShootingPattern::ShootingPattern *shootingPattern;
  std::vector<MovementPattern::MovementPattern *> movementPatterns;
  std::vector<ShootingPattern::ShootingPattern *> shootingPatterns;

  std::vector<std::pair<
    std::function<bool(const BoundingBox::BoundingBox<glm::vec3> &)>,
    std::function<void()>
  >> hitEventHandlers;

  void updateMovementPattern();
  void updateShootingPattern();
  ShootingPattern::ShootingPattern *chooseShootingPattern();
  void shooting();
};
} // namespace Enemy
#endif // ENEMY_HPP