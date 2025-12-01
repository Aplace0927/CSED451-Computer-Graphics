#include "player.hpp"

namespace BBong {
void Player::update() {
  direction = Input::getInstance().playerMoveVec;
  isShooting = Input::getInstance().isShooting;

  shootingCooldown += Utility::DeltaTime;
  reviveCooldown += Utility::DeltaTime;

  if (playerHealth <= 0) {
    this->setActive(false);
    return;
  }

  if (reviveCooldown >= GameConfig::REVIVE_COOLDOWN_TIME_SEC) {
    isLive = true;
    meshRenderer->gameObject->setActive(true);
  }

  animateViewDirection = glm::mix(animateViewDirection, direction, GameConfig::ANIMATION_BLEND_SPEED);
  transform->setRotation(glm::quat(glm::radians(glm::vec3(
      -90.0f + 20.0f * animateViewDirection.y, 180.0f + 10.0f * animateViewDirection.x, 0.0f))));

  healthGemOrigin->transform->rotate(90.0f * Utility::DeltaTime,
                                     glm::normalize(glm::vec3(0, 1, 1)));

  if (isShooting &&
      shootingCooldown >= GameConfig::SHOOTING_COOLDOWN_TIME_SEC) {
    auto newBullet = bullets->acquire();
#ifdef ASSETS_DIRECTORY
    newBullet->getComponent<MeshRenderer3D>()->setTextureID(
        TextureManager::getInstance().getTexture(
            ASSETS_DIRECTORY "texture/diffuse/diffuse_rice.png"));
#else
    newBullet->getComponent<MeshRenderer3D>()->setTextureID(
        TextureManager::getInstance().getTexture(
            "assets/texture/diffuse/diffuse_rice.png"));
#endif
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

void Player::lateUpdate() {
  if (shaking) {
    shakeTimer -= Utility::DeltaTime;
    if (shakeTimer <= 0.0f) {
      shaking = false;
      shakeTimer = 0.0f;

      ShaderManager::getInstance().attachProgram();
      ShaderManager::getInstance().setUniformValue<glm::mat4>(
          "uMat4CameraShake", glm::mat4(1.0f));
      ShaderManager::getInstance().detachProgram();
    }

    ShaderManager::getInstance().attachProgram();
    applyCameraShake();
  }
}

void Player::collision3D(Collider3D *collider) {
  if (playerHealth > 0 && isLive) {
    startCameraShake(0.15f, 3000.0f, 60.0f);
    --playerHealth;
    isLive = false;
    reviveCooldown = 0.0f;
    meshRenderer->gameObject->setActive(false);
    GameObject *lostHealthGem = healthGems.back();
    healthGems.pop_back();
    lostHealthGem->setActive(false);
  }
}

void Player::applyCameraShake() const {
  float offsetX = glm::sin(shakeTimer * shakeSpeed) * shakeMagnitude /
                  GameConfig::WINDOW_WIDTH;
  float offsetY = glm::cos(shakeTimer * shakeSpeed * 1.3f) * shakeMagnitude /
                  GameConfig::WINDOW_HEIGHT;

  glm::mat4 cameraShakeMatrix =
      glm::translate(glm::mat4(1.0f), glm::vec3(-offsetX, -offsetY, 0.0f));

  ShaderManager::getInstance().attachProgram();
  ShaderManager::getInstance().setUniformValue<glm::mat4>("uMat4CameraShake",
                                                          cameraShakeMatrix);
  ShaderManager::getInstance().detachProgram();
}

void Player::startCameraShake(float duration, float magnitude,
                                       float speed) {
  shakeDuration = duration;
  shakeMagnitude = magnitude;
  shakeSpeed = speed;
  shakeTimer = duration;
  shaking = true;
}
} // namespace BBong