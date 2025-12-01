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
#include "BBong/objloader.hpp"
#include "BBong/texturemanager.hpp"
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

  void setMoveDirection(const glm::vec3 &dir) {
    moveDirection = Utility::getNormalizedDirection(dir, 1.0f);
  }

  void setBulletSpeed(float speed) { BulletSpeed = speed; } 

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
    meshRenderer->setMesh(ObjLoader::load(ASSETS_DIRECTORY "obj/rice.obj"));
    meshRenderer->setTexture(
        TextureManager::getInstance().getTexture(
            ASSETS_DIRECTORY "texture/diffuse/diffuse_rice.png"));
#else
    printf("Warning: ASSETS_DIRECTORY not defined.\n");
    meshRenderer->setMesh(ObjLoader::load("assets/obj/rice.obj"));
    meshRenderer->setTexture(
        TextureManager::getInstance().getTexture(
            "assets/texture/diffuse/diffuse_rice.png"));
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
    meshRenderer->setMesh(ObjLoader::load(ASSETS_DIRECTORY "obj/rice.obj"));
    meshRenderer->setTexture(
        TextureManager::getInstance().getTexture(
            ASSETS_DIRECTORY "texture/diffuse/diffuse_sonic_1.png"));
#else
    printf("Warning: ASSETS_DIRECTORY not defined.\n");
    meshRenderer->setMesh(ObjLoader::load("assets/obj/rice.obj"));
    meshRenderer->setTexture(
        TextureManager::getInstance().getTexture(
            "assets/texture/diffuse/diffuse_sonic_1.png"));
#endif
    meshRenderer->setDefaultColor(glm::vec3(0.6f, 0.2f, 0.2f));

    transform->setScale(glm::vec3(2.0f));

    auto collider = addComponent<BoxCollider3D>();
    collider->setLayer(GameConfig::CollisionLayer::ENEMY_BULLET);
    std::vector<glm::vec3> vertices = {glm::vec3(-0.5f, -0.5f, -0.5f),
                                       glm::vec3(0.5f, 0.5f, 0.5f)};
    collider->SetBoundingBox(vertices);
  }
};
} // namespace BBong

#endif // BULLET_HPP