#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <memory>

#include "BBong/gameobject.hpp"
#include "BBong/renderer3d.hpp"
#include "BBong/collider3d.hpp"
#include "BBong/collisionmanager.hpp"
#include "BBong/component.hpp"
#include "BBong/objfileloader.hpp"
#include "objectpool.hpp"
#include "config.hpp"
#include "bullet.hpp"

namespace BBong {
class Player : public ClonableComponent<Player> {
public:
  explicit Player(GameObject *owner)
      : ClonableComponent(owner), meshRenderer(nullptr) // ��� ���� �ʱ�ȭ �߰�
  {
    // Player Bullet Object
    GameObject *bulletPrefab = createBulletPrefab();
    bullets = std::make_shared<ObjectPool>(*bulletPrefab, nullptr, 0);
    bulletPrefab->getComponent<Bullet>()->SetBulletPool(bullets);

    // Player Mesh Component
    GameObject * renderObj =
        Game::getInstance().mainScene->createGameObject(transform);
    meshRenderer = renderObj->addComponent<MeshRenderer3D>();

#ifdef ASSETS_DIRECTORY
    meshRenderer->setMesh(ObjFileLoader::load(ASSETS_DIRECTORY "jet.obj"));
#else
    printf("Warning: ASSETS_DIRECTORY not defined.\n");
    meshRenderer->setMesh(ObjFileLoader::load("assets/jet.obj"));
#endif
    meshRenderer->setDefaultColor(glm::vec3(0.0f, 1.0f, 1.0f));

    transform->setWorldPosition(glm::vec3(0.0f, -GameConfig::WINDOW_HEIGHT / 4.0f, 0.0f));
    transform->setScale(glm::vec3(5.0f));

    transform->setRotation(glm::quat(glm::vec3(0.0f)));
    shootingPoint = Game::getInstance().mainScene->createGameObject(transform);
    shootingPoint->transform->setLocalPosition(glm::vec3(0, 0, 7));

    // Player Health Gem Origin
    healthGemOrigin =
        Game::getInstance().mainScene->createGameObject(transform);

    for (int i = 0; i < playerHealth; ++i) {
      GameObject *healthGem =
          Game::getInstance().mainScene->createGameObject(transform);
      healthGem->transform->setLocalPosition(glm::vec3(
          10 * glm::cos(glm::radians(360.0f * i / playerHealth)),
          10 * glm::sin(glm::radians(360.0f * i / playerHealth)), 0.0f));
      auto healthGemMesh = healthGem->addComponent<MeshRenderer3D>();
#ifdef ASSETS_DIRECTORY
      healthGemMesh->setMesh(ObjFileLoader::load(ASSETS_DIRECTORY "star.obj"));
#else
      printf("Warning: ASSETS_DIRECTORY not defined.\n");
      healthGemMesh->setMesh(ObjFileLoader::load("assets/star.obj"));
#endif
      healthGemMesh->setDefaultColor(glm::vec3(1.0f, 1.0f, 0.5f));
      healthGem->transform->setParent(
          healthGemOrigin->transform); // Set rotation center
      healthGems.push_back(healthGem);

      // Player Collider
      auto collider = addComponent<BoxCollider3D>();
      collider->setLayer(GameConfig::CollisionLayer::PLAYER);
      std::vector<glm::vec3> vertices = {glm::vec3(-3.0f, -3.0f, -3.0f),
                                         glm::vec3(3.0f, 3.0f, 3.0f)};
      collider->SetBoundingBox(vertices);
    } // for loop brace was missing in provided snippet, assumed closed here
  };

  Player(const Player &other)
      : ClonableComponent(nullptr),
        meshRenderer(nullptr)
  {
    this->bullets = other.bullets;
    this->direction = other.direction;
    this->shootingPoint = other.shootingPoint;
    this->healthGemOrigin = other.healthGemOrigin;
    this->healthGems = other.healthGems;
  }

  ~Player() override { bullets.reset(); }

  void update() override;
  void lateUpdate() override;
  void fixedUpdate() override;
  void collision3D(Collider3D *collider) override;

private:
  static GameObject *createBulletPrefab() {
    auto bulletPrefab = Game::getInstance().mainScene->createGameObject();
    bulletPrefab->setActive(false);
    bulletPrefab->addComponent<PlayerBullet>();
    return bulletPrefab;
  }

  void startCameraShake(float duration, float magnitude, float speed);
  void applyCameraShake() const;

  bool shaking = false;
  float shakeDuration = 0.0f;
  float shakeTimer = 0.0f;
  float shakeMagnitude = 0.0f;
  float shakeSpeed = 0.0f;

  std::shared_ptr<ObjectPool> bullets;
  glm::vec3 animateViewDirection = glm::vec3(0.0f);
  glm::vec3 direction = glm::vec3(0.0f);
  GameObject* shootingPoint;
  GameObject* healthGemOrigin;
  MeshRenderer3D *meshRenderer = nullptr; // ������ �ʱ�ȭ
  std::vector<GameObject*> healthGems;
  int playerHealth = 10;
  float shootingCooldown = 0.0f;
  float reviveCooldown = 0.0f;
  float speed = 100.0f;
  bool isShooting = false;
  bool isLive = true;
};
} // namespace BBong
#endif // PLAYER_HPP