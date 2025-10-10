#include "bullet.hpp"
#include <iostream>

namespace Bullet {
Bullet::Bullet(Shape::RGBColor color)
    : Object::Object(
      Transform::createBullet(color)   
    ),
      bullet_origin(glm::vec3(0.0f, 0.0f, 0.0f)),
      movement_pattern(BulletPattern::empty()),
      bullet_shooter(BulletType::NONE) {
  Object::setStatus(false);
}

void Bullet::deactivate() {
  Object::setStatus(false);
  bullet_origin = glm::vec3(0.0f, 0.0f, 0.0f);
  movement_pattern = BulletPattern::empty();
  bullet_shooter = BulletType::NONE;
  setReleaseFunction(nullptr);
  hitEventHandlers = {};
}

void Bullet::activate(
    glm::vec3 origin, std::function<glm::vec3(glm::vec3, float)> pattern,
    BulletType shooter, std::function<void()> releaseFunc,
    std::vector<std::pair<
        std::function<bool(const BoundingBox::BoundingBox<glm::vec3> &)>,
        std::function<void()>
    > > hitEventHandlerVec) {
  bullet_origin = origin;
  movement_pattern = pattern;
  bullet_shooter = shooter;
  setReleaseFunction(releaseFunc);
  hitEventHandlers = hitEventHandlerVec;
  Object::setStatus(true);
  setPosition(movement_pattern(bullet_origin, 0));
  
  // We should patch the code pattern like following:

  getTransform()->transformMatrix = glm::translate(
      glm::identity<glm::mat4>(),
      bullet_origin
  );
}

void Bullet::update(float time) {
  if (!Object::getStatus()) {
    return;
  }
  Object::draw(time);
}

void Bullet::fixedUpdate() {
  if (!Object::getStatus()) {
    return;
  }

  setPosition(movement_pattern(getCenter(), GameConfig::FIXED_DELTATIME));

  if (!Utility::isInRenderBounds(getCenter())) {
    callReleaseFunction();
    return;
  }

  for (const auto &handlerPair : hitEventHandlers) {
    if (handlerPair.first(getBoundingBox())) {
      handlerPair.second();
      callReleaseFunction();
      return;
    }
  }
}

PlayerBullet::PlayerBullet()
    : Bullet(static_cast<Shape::RGBColor>(
          glm::make_vec3(GameConfig::PLAYER_BULLET_COLOR))) {}

EnemyBullet::EnemyBullet()
    : Bullet(static_cast<Shape::RGBColor>(
          glm::make_vec3(GameConfig::ENEMY_BULLET_COLOR))) {}
} // namespace Bullet