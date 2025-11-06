#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <memory>

#include "BBong/objectpool.hpp"
#include "BBong/gameobject.hpp"
#include "BBong/renderer3d.hpp"
#include "BBong/collider3d.hpp"
#include "BBong/component.hpp"
#include "BBong/objfileloader.hpp"
#include "config.hpp"
#include "bullet.hpp"
#include "gamestate.hpp"
#include "mesh2dsample.hpp"

extern BBong::GameState gameState;

namespace BBong {
class Player : public ClonableComponent<Player> {
public:
  explicit Player(GameObject *owner)
      : ClonableComponent(owner) {

    GameObject *bulletPrefab = createBulletPrefab();
    bullets = std::make_shared<ObjectPool>(*bulletPrefab, nullptr, 0);
    bulletPrefab->getComponent<Bullet>()->SetBulletPool(bullets);

    auto meshRenderer = addComponent<MeshRenderer3D>();
    
    #ifdef ASSETS_DIRECTORY
      meshRenderer->SetMesh(ObjFileLoader::load(ASSETS_DIRECTORY "jet.obj"));
    #else
      printf("Warning: ASSETS_DIRECTORY not defined.\n");
      meshRenderer->SetMesh(ObjFileLoader::load("assets/jet.obj"));
    #endif

    addComponent<BoxCollider3D>();

    transform->setScale(glm::vec3(5.0f));
    transform->setRotation(
        glm::quat(glm::radians(glm::vec3(90.0f, 0.0f, 180.0f))));

    shootingPoint = Game::getInstance().mainScene->createGameObject(transform);
    shootingPoint->transform->setWorldPosition(glm::vec3(0, 30, 0));
  };

  Player(const Player &other) : ClonableComponent(nullptr) {
    this->bullets = other.bullets;
    this->direction = other.direction;
    this->shootingPoint = other.shootingPoint;
  }

  ~Player() override { bullets.reset(); }

  void update() override;
  void fixedUpdate() override;

private:
  static GameObject *createBulletPrefab() {
    auto bulletPrefab = Game::getInstance().mainScene->createGameObject();
    bulletPrefab->setActive(false);
    bulletPrefab->addComponent<PlayerBullet>();
    return bulletPrefab;
  }

  std::shared_ptr<ObjectPool> bullets;
  glm::vec3 direction = glm::vec3(0.0f);
  GameObject* shootingPoint;
  int playerHealth = 100;
  float shootingCooldown = 0.0f;
  float reviveCooldown = 0.0f;
  float speed = 100.0f;
  bool isShooting = false;
};
} // namespace BBong
#endif // PLAYER_HPP