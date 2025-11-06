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

enum class BulletType { PLAYER, ENEMY, NONE };

class Bullet : public ClonableComponent<Bullet> {
public:
  explicit Bullet(GameObject *owner)
      : ClonableComponent(owner), bullet_shooter(BulletType::NONE),
        moveDirection(0) {}

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

protected:
  float BulletSpeed = 300.0f;
  BulletType bullet_shooter;
  glm::vec3 moveDirection;

private:
  std::shared_ptr<ObjectPool> bulletPool;
};

class PlayerBullet : public Bullet {
public:
  explicit PlayerBullet(GameObject *owner) : Bullet(owner) {
    auto meshRenderer = addComponent<MeshRenderer3D>();
    
    #ifdef ASSETS_DIRECTORY
      meshRenderer->SetMesh(ObjFileLoader::load(ASSETS_DIRECTORY "rice.obj"));
    #else
      printf("Warning: ASSETS_DIRECTORY not defined.\n");
      meshRenderer->SetMesh(ObjFileLoader::load("assets/rice.obj"));
    #endif

    transform->setScale(glm::vec3(2.0f));
    
    addComponent<BoxCollider3D>();
    bullet_shooter = BulletType::PLAYER;
    moveDirection = glm::vec3(0.0f, 1.0f, 0.0f);
  }
};

class EnemyBullet : public Bullet {
public:
  explicit EnemyBullet(GameObject *owner) : Bullet(owner) {
    auto meshRenderer = addComponent<MeshRenderer3D>();
    
    #ifdef ASSETS_DIRECTORY
      meshRenderer->SetMesh(ObjFileLoader::load(ASSETS_DIRECTORY "rice.obj"));
    #else
      printf("Warning: ASSETS_DIRECTORY not defined.\n");
      meshRenderer->SetMesh(ObjFileLoader::load("assets/rice.obj"));
    #endif

    addComponent<BoxCollider3D>();
    bullet_shooter = BulletType::ENEMY;
    moveDirection = glm::vec3(0.0f, -1.0f, 0.0f);
  }
};
} // namespace BBong

#endif // BULLET_HPP