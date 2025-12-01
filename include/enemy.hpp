#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <cmath>

#include "BBong/gameobject.hpp"
#include "BBong/component.hpp"
#include "BBong/renderer3d.hpp"
#include "BBong/collider3d.hpp"
#include "BBong/texturemanager.hpp"
#include "healthbar.hpp"
#include "objectpool.hpp"
#include "bullet.hpp"
#include "enemypatterns.hpp"

namespace BBong {
class Enemy : public ClonableComponent<Enemy> {
public:
  explicit Enemy(GameObject *owner) : ClonableComponent(owner) {

    GameObject *bulletPrefab = createBulletPrefab();
    bullets = std::make_shared<ObjectPool>(*bulletPrefab, nullptr, 0);
    bulletPrefab->getComponent<Bullet>()->SetBulletPool(bullets);

    auto meshRenderer = addComponent<MeshRenderer3D>();
#ifdef ASSETS_DIRECTORY
    meshRenderer->setMesh(ObjLoader::load(ASSETS_DIRECTORY "obj/starship.obj"));
    meshRenderer->setTexture(
        TextureManager::getInstance().getTexture(
            ASSETS_DIRECTORY "texture/diffuse/diffuse_starship.png"));
#else
    printf("Warning: ASSETS_DIRECTORY not defined.\n");
    meshRenderer->setMesh(ObjLoader::load("assets/obj/starship.obj"));
    meshRenderer->setTexture(
        TextureManager::getInstance().getTexture(
            "assets/texture/diffuse/diffuse_starship.png"));
#endif
    meshRenderer->setDefaultColor(glm::vec3(0.5f, 0.0f, 0.5f));

    transform->setScale(glm::vec3(100.0f));
    transform->setRotation(
        glm::quat(glm::radians(glm::vec3(90.0f, 0.0f, 0.0f))));

    shootingPattern = chooseShootingPattern();

    // Set up health bar
    healthBar = Game::getInstance().mainScene->createGameObject(transform);
    healthBar->transform->setScale(glm::vec3(0.2f));
    healthBar->transform->setLocalPosition(glm::vec3(0.0f, 0.2f, 0.2f));
    
    auto healthBarMesh = healthBar->addComponent<MeshRenderer3D>();
    healthBarMesh->setMesh(createHealthBarMesh(enemyHealth, enemyMaxHealth));
    healthBarMesh->forceGraphicStyleMode(GraphicStyle::OPAQUE_POLYGON);
    healthBarMesh->setDefaultColor(glm::vec3(0.0f, 1.0f, 0.0f));
     
    // Set up collider
    auto collider = addComponent<BoxCollider3D>();
    collider->setLayer(GameConfig::CollisionLayer::ENEMY);
    std::vector<glm::vec3> vertices = {glm::vec3(-0.3f, -0.3f, -0.6f),
                                       glm::vec3(0.3f, 0.3f, 0.3f)};
    collider->SetBoundingBox(vertices);
  };

  Enemy(const Enemy &other) : ClonableComponent(nullptr) {
    this->healthBar = Game::getInstance().mainScene->Instantiate(*other.healthBar);
    this->bullets = other.bullets;
    this->shootingPattern = other.shootingPattern;
    this->shootingPatterns = other.shootingPatterns;
  }

  void update() override;
  void fixedUpdate() override;
  void collision3D(Collider3D *collider) override;

private:
  static GameObject *createBulletPrefab() {
    auto bulletPrefab = Game::getInstance().mainScene->createGameObject();
    bulletPrefab->setActive(false);
    bulletPrefab->addComponent<EnemyBullet>();
    return bulletPrefab;
  }
  void updateMovementPattern();
  void updateShootingPattern();
  ShootingPattern *chooseShootingPattern();
  void shooting();

  GameObject* healthBar;
  std::shared_ptr<ObjectPool> bullets;
  std::vector<MovementPattern *> movementPatterns{new HorizonPattern(10.0f),
                                                  new FallingPattern(5.0f)};
  ShootingPattern *shootingPattern;
  std::vector<ShootingPattern *> shootingPatterns{
      new CirclePattern(200.0f, 12), new SpiralPattern(200.0f, 20.0f),
      new RandomBurstPattern(250.0f, 5)};
  int enemyHealth = 100;
  int enemyMaxHealth = 100;
};
} // namespace BBong
#endif // ENEMY_HPP