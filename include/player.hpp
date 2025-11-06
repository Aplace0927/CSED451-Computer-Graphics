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

    // Player Object
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

    // Player Bullet Shooting Point
    transform->setWorldPosition(
        glm::vec3(0.0f, -GameConfig::WINDOW_HEIGHT / 4.0f, 0.0f)
    );
    transform->setScale(glm::vec3(5.0f));
    transform->setRotation(
        glm::quat(glm::radians(glm::vec3(90.0f, 0.0f, 180.0f))));

    shootingPoint = Game::getInstance().mainScene->createGameObject(transform);
    shootingPoint->transform->setLocalPosition(glm::vec3(0, 0, 7));

    // Player Health Gem Origin
    healthGemOrigin = Game::getInstance().mainScene->createGameObject(transform);

    for (int i = 0; i < playerHealth; ++i) {
      GameObject* healthGem = Game::getInstance().mainScene->createGameObject(transform);
      healthGem->transform->setLocalPosition(
        glm::vec3(
          10 * glm::cos(glm::radians(360.0f * i / playerHealth)),
          10 * glm::sin(glm::radians(360.0f * i / playerHealth)),
          0.0f
        )
      );
      auto healthGemMesh = healthGem->addComponent<MeshRenderer3D>();
      #ifdef ASSETS_DIRECTORY
        healthGemMesh->SetMesh(ObjFileLoader::load(ASSETS_DIRECTORY "star.obj"));
      #else
        printf("Warning: ASSETS_DIRECTORY not defined.\n");
        healthGemMesh->SetMesh(ObjFileLoader::load("assets/star.obj"));
      #endif
      healthGem->transform->setParent(healthGemOrigin->transform);  // Set rotation center
      healthGems.push_back(healthGem);
    }
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
  GameObject* healthGemOrigin;
  std::vector<GameObject*> healthGems;
  int playerHealth = 10;
  float shootingCooldown = 0.0f;
  float reviveCooldown = 0.0f;
  float speed = 100.0f;
  bool isShooting = false;
};
} // namespace BBong
#endif // PLAYER_HPP