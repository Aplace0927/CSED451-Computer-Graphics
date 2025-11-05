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
      : ClonableComponent(owner),
        bullets(new ObjectPool(*createBulletPrefab(), nullptr, 100)) {
    auto meshRenderer = addComponent<MeshRenderer3D>();
    //meshRenderer->SetMesh(createRainbowHexagonMesh(100));
    meshRenderer->SetMesh(ObjFileLoader::load("../assets/jet.obj"));
    addComponent<BoxCollider3D>();

    transform->setScale(glm::vec3(5.0f));
    transform->setRotation(glm::quat(glm::radians(glm::vec3(90.0f, 0.0f, 180.0f))));
  };

  Player(const Player &other) : ClonableComponent(nullptr) {
    this->bullets = other.bullets;
  }

  ~Player() override { bullets.reset(); }

  void update() override;
  void fixedUpdate() override;
  void setDirection(const glm::vec3 &input) { direction = input; }
  void shooting(bool shooting) {
    isShooting = shooting;
    if (!isShooting) {
      shootingCooldown = 0;
    }
  }

private:
  static GameObject *createBulletPrefab() {
    auto bulletPrefab = Game::getInstance().mainScene->createGameObject();
    bulletPrefab->setActive(false);
    bulletPrefab->addComponent<PlayerBullet>();
    return bulletPrefab;
  }

  std::shared_ptr<ObjectPool> bullets;
  glm::vec3 direction = glm::vec3(0.0f);
  int playerHealth = 100;
  float shootingCooldown = 0.0f;
  float reviveCooldown = 0.0f;
  float speed = 100.0f;
  bool isShooting = false;
};
} // namespace BBong
#endif // PLAYER_HPP