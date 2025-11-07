#include "player.hpp"

#include "BBong/input.hpp"

namespace BBong {
void Player::update() {
  direction = Input::getInstance().playerMoveVec;
  isShooting = Input::getInstance().isShooting;

  shootingCooldown += Utility::DeltaTime;
  reviveCooldown += Utility::DeltaTime;

  if (reviveCooldown >= GameConfig::REVIVE_COOLDOWN_TIME_SEC) {
    isLive = true;
    meshRenderer->gameObject->setActive(true);
  }

  transform->setRotation(glm::quat(glm::radians(glm::vec3(
      -90.0f + 20.0f * direction.y, 180.0f + 10.0f * direction.x, 0.0f))));

  healthGemOrigin->transform->rotate(90.0f * Utility::DeltaTime,
                                     glm::vec3(0, 0, 1));

  if (isShooting &&
      shootingCooldown >= GameConfig::SHOOTING_COOLDOWN_TIME_SEC) {
    auto newBullet = bullets->acquire();
    newBullet->transform->setWorldPosition(
        shootingPoint->transform->getWorldPosition());
    shootingCooldown = 0;
  }
}

void Player::fixedUpdate() {
  transform->translate(direction * Utility::FixedDeltaTime * speed);

  glm::vec3 currentpos = transform->getWorldPosition();

  transform->setWorldPosition(
      glm::vec3(glm::clamp(currentpos.x, GameConfig::POSITION_LEFT_LIMIT,
                           GameConfig::POSITION_RIGHT_LIMIT),
                glm::clamp(currentpos.y, GameConfig::POSITION_LOWER_LIMIT,
                           GameConfig::POSITION_UPPER_LIMIT),
                currentpos.z));
}

void Player::collision3D(Collider3D *collider) {
  if (playerHealth > 0 && isLive) {
    GraphicsManager::getInstance().startCameraShake(0.15f, 1.5f, 60.0f);
    --playerHealth;
    isLive = false;
    reviveCooldown = 0.0f;
    meshRenderer->gameObject->setActive(false);
    GameObject *lostHealthGem = healthGems.back();
    healthGems.pop_back();
    lostHealthGem->setActive(false);
  }
}
} // namespace BBong