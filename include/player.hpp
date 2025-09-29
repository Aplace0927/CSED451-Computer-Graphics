#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "object.hpp"
#include "config.hpp"
#include "objectpool.hpp"
#include "bullet.hpp"
#include "healthbar.hpp"
#include "graphicsmanager.hpp"
#include "gamestate.hpp"

extern GameState::GameState gameState;

namespace Player {
class Player : public Object::Object<glm::vec3, Shape::RGBColor> {
public:
  Player();
  void update(float time) override;
  void fixedUpdate() override;
  void setDirection(const glm::vec3 &input) { direction = input; }
  void shooting(bool shooting) {
    isShooting = shooting;
    if (!isShooting) {
      shootingCooldown = 0;
    }
  }

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
      GraphicsManager::GraphicsManager::getInstance().startCameraShake(
          0.5f, 10.0f, 20.0f);
      playerHealth = glm::max(0, playerHealth - 1);
      healthBar.setCurrentHealth(playerHealth);
      if (playerHealth == 0) {
        gameState = GameState::GameState::LOSE;
      } else {
        reviveCooldown = 0;
        this->setStatus(false);
      }
    };
  }

private:
  // Add player state variables here
  int playerHealth;
  glm::vec3 direction;
  bool isShooting;
  float shootingCooldown;
  float reviveCooldown;

  HealthBar::HealthBar healthBar;
  ObjectPool::ObjectPool<Bullet::PlayerBullet> bullets;
  std::function<bool(const BoundingBox::BoundingBox<glm::vec3> &)>
      bulletHitDetectFunction;
  std::function<void()> bulletHitEventFunction;
};
}; // namespace Player
#endif // PLAYER_HPP