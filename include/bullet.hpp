#ifndef BULLET_HPP 
#define BULLET_HPP

#include <functional>
#include <iostream>
#include <memory>
#include <glm/glm.hpp>

#include "BBong/renderer3d.hpp"
#include "BBong/component.hpp"
#include "BBong/collider3d.hpp"
#include "BBong/gameobject.hpp"
#include "BBong/transform.hpp"
#include "BBong/objfileloader.hpp"
#include "objectpool.hpp"
#include "utility.hpp"
#include "config.hpp"

namespace BBong {

class Bullet : public ClonableComponent<Bullet> {
public:
  explicit Bullet(GameObject *owner)
      : ClonableComponent(owner), moveDirection(0) {}

  Bullet(const Bullet &other) : ClonableComponent(nullptr) {
    this->bulletPool = other.bulletPool;
    this->moveDirection = other.moveDirection;
  }

  void SetBulletPool(std::shared_ptr<ObjectPool> pool) { bulletPool = pool; }

  void fixedUpdate() override {
    transform->translate(moveDirection * BulletSpeed * Utility::FixedDeltaTime);

    glm::vec3 currentPos = transform->getWorldPosition();
    if (currentPos.x < GameConfig::POSITION_LEFT_LIMIT ||
        currentPos.x > GameConfig::POSITION_RIGHT_LIMIT ||
        currentPos.y < GameConfig::POSITION_LOWER_LIMIT ||
        currentPos.y > GameConfig::POSITION_UPPER_LIMIT)
      bulletPool->release(gameObject);
  };

  void collision3D(Collider3D *collider) override {
    bulletPool->release(gameObject);
  };

protected:
  float BulletSpeed = 300.0f;
  glm::vec3 moveDirection;

private:
  std::shared_ptr<ObjectPool> bulletPool;
};

class PlayerBullet : public Bullet {
public:
  explicit PlayerBullet(GameObject *owner) : Bullet(owner) {
    auto meshRenderer = addComponent<MeshRenderer3D>();

#ifdef ASSETS_DIRECTORY
    meshRenderer->setMesh(ObjFileLoader::load(ASSETS_DIRECTORY "rice.obj"));
#else
    printf("Warning: ASSETS_DIRECTORY not defined.\n");
    meshRenderer->setMesh(ObjFileLoader::load("assets/rice.obj"));
#endif
    meshRenderer->setDefaultColor(glm::vec3(0.0f, 1.0f, 0.0f));

    transform->setScale(glm::vec3(2.0f));

    auto collider = addComponent<BoxCollider3D>();
    collider->setLayer(GameConfig::CollisionLayer::PLAYER_BULLET);
    std::vector<glm::vec3> vertices = {glm::vec3(-0.5f, -0.5f, -0.5f),
                                       glm::vec3(0.5f, 0.5f, 0.5f)};
    collider->SetBoundingBox(vertices);

    moveDirection = glm::vec3(0.0f, 1.0f, 0.0f);
  }
};

class EnemyBullet : public Bullet {
public:
  explicit EnemyBullet(GameObject *owner) : Bullet(owner) {
    auto meshRenderer = addComponent<MeshRenderer3D>();

#ifdef ASSETS_DIRECTORY
    meshRenderer->setMesh(ObjFileLoader::load(ASSETS_DIRECTORY "rice.obj"));
#else
    printf("Warning: ASSETS_DIRECTORY not defined.\n");
    meshRenderer->setMesh(ObjFileLoader::load("assets/rice.obj"));
#endif
    meshRenderer->setDefaultColor(glm::vec3(1.0f, 0.0f, 0.5f));

    transform->setScale(glm::vec3(2.0f));

    auto collider = addComponent<BoxCollider3D>();
    collider->setLayer(GameConfig::CollisionLayer::ENEMY_BULLET);
    std::vector<glm::vec3> vertices = {glm::vec3(-0.5f, -0.5f, -0.5f),
                                       glm::vec3(0.5f, 0.5f, 0.5f)};
    collider->SetBoundingBox(vertices);

    moveDirection = glm::vec3(0.0f, -1.0f, 0.0f);
  }
};
} // namespace BBong

#endif // BULLET_HPP