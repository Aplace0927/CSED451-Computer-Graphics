#include "player.hpp"

namespace Player {
Player::Player()
    : GameObject::GameObject(
      Transform::createPlayer()
  )
      // playerHealth(GameConfig::PLAYER_LIFE), isShooting(false),
      // healthBar(glm::vec3(GameConfig::PLAYER_DIGIT_X,
      //                     GameConfig::PLAYER_DIGIT_Y, 0.0f),
      //           GameConfig::FONT_DIGIT_SIZE,
      //           glm::vec3(GameConfig::PLAYER_GAUGE_X,
      //                     GameConfig::PLAYER_GAUGE_Y, 0.0f),
      //           GameConfig::PLAYER_GAUGE_WIDTH, GameConfig::PLAYER_GAUGE_HEIGHT,
      //           playerHealth)
                {
  shootingCooldown = 0;
  bullets = ObjectPool::ObjectPool<Bullet::PlayerBullet>();
  playerHealth = GameConfig::PLAYER_LIFE;
  isShooting = false;
  direction = glm::vec3(0.0f, 0.0f, 0.0f);
}

void Player::update(float time) {
  if (gameState == GameState::GameState::LOSE) {
    this->setStatus(false);
    //healthBar.setStatus(false);
    return;
  }

  shootingCooldown += time;
  reviveCooldown += time;

  if (!getStatus() && reviveCooldown >= GameConfig::REVIVE_COOLDOWN_TIME_SEC) {
    this->setStatus(true);
  }

  if (isShooting &&
      shootingCooldown >= GameConfig::SHOOTING_COOLDOWN_TIME_SEC) {
    Bullet::PlayerBullet *newBullet = bullets.acquire();
    newBullet->activate(
        getCenter() + glm::vec3(0.0f, 17.3f, 0.0f),
        BulletPattern::straight(glm::vec3(0, 1.0f, 0), 400.0f),
        Bullet::BulletType::PLAYER,
        [this, newBullet]() { this->bullets.release(newBullet); },
        bulletHitDetectFunction, bulletHitEventFunction);
    shootingCooldown = 0;
  }

  if (this->getStatus()) {
    draw(Utility::getCurrentTimeMS());
  }
}

void Player::fixedUpdate() {
  if (!getStatus()) {
    return;
  }
  move(direction);
  glm::vec3 currentPos = getSceneGraph()->getCenter();
  BoundingBox::BoundingBox<glm::vec3> bdbx = getSceneGraph()->getBoundingBox(Utility::getCurrentTimeMS());

  setPosition(
      glm::vec3(glm::clamp(currentPos.x, GameConfig::POSITION_LEFT_LIMIT,
                           GameConfig::POSITION_RIGHT_LIMIT),
                glm::clamp(currentPos.y, GameConfig::POSITION_LOWER_LIMIT,
                           GameConfig::POSITION_UPPER_LIMIT),
                currentPos.z));
}
} // namespace Player