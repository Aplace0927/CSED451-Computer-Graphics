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
#include "utility.hpp"
#include "config.hpp"

namespace BBong {

enum class BulletType { PLAYER, ENEMY, NONE };

class Bullet : public ClonableComponent<Bullet> {
public:
  explicit Bullet(GameObject *owner) : ClonableComponent(owner) {}

  void fixedUpdate() override {
    transform->setPosition(transform->position + moveDirection * BulletSpeed *
                                                     Utility::FixedDeltaTime);
  };

protected:
  float BulletSpeed = 300.0f;
  BulletType bullet_shooter;
  glm::vec3 moveDirection;
};

class PlayerBullet : public Bullet {
public:
  explicit PlayerBullet(GameObject *owner) : Bullet(owner) {
    auto meshRenderer = addComponent<MeshRenderer3D>();
    meshRenderer->SetMesh(ObjFileLoader::load("assets/rice.obj"));
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
    meshRenderer->SetMesh(ObjFileLoader::load("assets/rice.obj"));

    addComponent<BoxCollider3D>();
    bullet_shooter = BulletType::ENEMY;
    moveDirection = glm::vec3(0.0f, -1.0f, 0.0f);
  }
};
} // namespace BBong

#endif // BULLET_HPP