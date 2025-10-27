#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <cmath>

#include "BBong/gameobject.hpp"
#include "BBong/objectpool.hpp"
#include "BBong/component.hpp"
#include "BBong/renderer2d.hpp"
#include "BBong/collider2d.hpp"
#include "bullet.hpp"
#include "enemypatterns.hpp"
#include "gamestate.hpp"

extern BBong::GameState gameState;

namespace BBong {
class Enemy : public ClonableComponent<Enemy> {
public:
  explicit Enemy(GameObject *owner)
      : ClonableComponent(owner) {
          // addComponent<MeshRenderer2D>();
          // addComponent<BoxCollider2D>();

          //// Create a prefab GameObject for enemy bullets and initialize pool
          // GameObject *bulletPrefab =
          // Game::getInstance().mainScene->createGameObject();
          // bulletPrefab->addComponent<EnemyBullet>();

          // shootingPatterns = {new CirclePattern(200.0f, 12),
          //                    new SpiralPattern(200.0f, 20.0f),
          //                    new RandomBurstPattern(250.0f, 5)};
          // shootingPattern = chooseShootingPattern();
          // movementPattern = new HorizonPattern(100.0f);
        };
  //void update() override;
  //void fixedUpdate() override;

private:
  int enemyHealth = 100;
  // ObjectPool bullets;
  // HealthBar::HealthBar healthBar;

  MovementPattern *movementPattern;
  ShootingPattern *shootingPattern;
  std::vector<ShootingPattern *> shootingPatterns{
      new CirclePattern(200.0f, 12), new SpiralPattern(200.0f, 20.0f),
      new RandomBurstPattern(250.0f, 5)};

  void updateMovementPattern();
  void updateShootingPattern();
  ShootingPattern *chooseShootingPattern();
  void shooting();
};
} // namespace BBong
#endif // ENEMY_HPP