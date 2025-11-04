#include "player.hpp"

#include "BBong/input.hpp"

namespace BBong {
void Player::update() {
  direction = Input::getInstance().playerMoveVec;
  isShooting = Input::getInstance().isShooting;

  shootingCooldown += Utility::DeltaTime;
  reviveCooldown += Utility::DeltaTime;

  if (!getActive() && reviveCooldown >= GameConfig::REVIVE_COOLDOWN_TIME_SEC) {
    this->setActive(true);
  }

  if (isShooting &&
      shootingCooldown >= GameConfig::SHOOTING_COOLDOWN_TIME_SEC) {
    auto newbullet = bullets->acquire();
    newbullet->transform->setPosition(transform->position);
    shootingCooldown = 0;
  }
}

void Player::fixedUpdate() {
  transform->setPosition(transform->position +
                         direction * Utility::FixedDeltaTime * speed);

  glm::vec3 currentpos = transform->position;

  transform->setPosition(
      glm::vec3(glm::clamp(currentpos.x, GameConfig::POSITION_LEFT_LIMIT,
                           GameConfig::POSITION_RIGHT_LIMIT),
                glm::clamp(currentpos.y, GameConfig::POSITION_LOWER_LIMIT,
                           GameConfig::POSITION_UPPER_LIMIT),
                currentpos.z));
}
} // namespace Player