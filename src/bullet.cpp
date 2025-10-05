#include "bullet.hpp"
#include <iostream>

namespace Bullet {
Bullet::Bullet(Shape::RGBColor color)
    : Object::Object(
      glm::vec3(0.0f, 0.0f, 0.0f),
      SceneGraph::createBullet(color)   
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
  hitDetectFunction = nullptr;
  hitEventFunction = nullptr;
}

void Bullet::activate(
    glm::vec3 origin, std::function<glm::vec3(glm::vec3, float)> pattern,
    BulletType shooter, std::function<void()> releaseFunc,
    std::function<bool(const BoundingBox::BoundingBox<glm::vec3> &)>
        hitDetectFunc,
    std::function<void()> hitEventFunc) {
  bullet_origin = origin;
  movement_pattern = pattern;
  bullet_shooter = shooter;
  setReleaseFunction(releaseFunc);
  hitDetectFunction = hitDetectFunc;
  hitEventFunction = hitEventFunc;
  Object::setStatus(true);
  setPosition(movement_pattern(bullet_origin, 0));
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

  if (hitDetectFunction(getBoundingBox())) {
    hitEventFunction();
    callReleaseFunction();
  }
}

PlayerBullet::PlayerBullet()
    : Bullet(static_cast<Shape::RGBColor>(
          glm::make_vec3(GameConfig::PLAYER_BULLET_COLOR))) {}

EnemyBullet::EnemyBullet()
    : Bullet(static_cast<Shape::RGBColor>(
          glm::make_vec3(GameConfig::ENEMY_BULLET_COLOR))) {}
} // namespace Bullet