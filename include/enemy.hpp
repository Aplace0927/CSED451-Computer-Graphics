#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <cmath>

#include "BBong/gameobject.hpp"
#include "BBong/objectpool.hpp"
#include "BBong/component.hpp"
#include "BBong/renderer3d.hpp"
#include "BBong/collider3d.hpp"
#include "bullet.hpp"
#include "enemypatterns.hpp"
#include "gamestate.hpp"

extern BBong::GameState gameState;

namespace BBong {
class Enemy : public ClonableComponent<Enemy> {
public:
  explicit Enemy(GameObject *owner)
      : ClonableComponent(owner){

    GameObject *bulletPrefab = createBulletPrefab();
    bullets = std::make_shared<ObjectPool>(*bulletPrefab, nullptr, 0);
    bulletPrefab->getComponent<Bullet>()->SetBulletPool(bullets);

    auto meshRenderer = addComponent<MeshRenderer3D>();
    meshRenderer->SetMesh(ObjFileLoader::load("assets/drone.obj"));

    addComponent<BoxCollider3D>();

    transform->setScale(glm::vec3(100.0f));
    transform->setRotation(
        glm::quat(glm::radians(glm::vec3(90.0f, 0.0f, 0.0f))));

    movementPattern = new HorizonPattern(100.0f);
    shootingPattern = chooseShootingPattern();
  };

  Enemy(const Enemy &other) : ClonableComponent(nullptr) {
    this->bullets = other.bullets;
    this->movementPattern = other.movementPattern;
    this->shootingPattern = other.shootingPattern;
  }

  void fixedUpdate() override;

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

  // HealthBar::HealthBar healthBar;
  std::shared_ptr<ObjectPool> bullets;
  MovementPattern *movementPattern;
  ShootingPattern *shootingPattern;
  std::vector<ShootingPattern *> shootingPatterns{
      new CirclePattern(200.0f, 12), new SpiralPattern(200.0f, 20.0f),
      new RandomBurstPattern(250.0f, 5)};
  int enemyHealth = 100;
};
} // namespace BBong
#endif // ENEMY_HPP