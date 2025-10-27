#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "BBong/objectpool.hpp"
#include "BBong/graphicsmanager.hpp"
#include "BBong/gameobject.hpp"
#include "BBong/renderer2d.hpp"
#include "BBong/collider2d.hpp"
#include "BBong/component.hpp"
#include "config.hpp"
#include "bullet.hpp"
#include "gamestate.hpp"

extern BBong::GameState gameState;

namespace BBong {
class Player : public ClonableComponent<Player> {
public:
  explicit Player(GameObject *owner)
      : ClonableComponent(owner) {
    addComponent<MeshRenderer2D>();
    //addComponent<BoxCollider2D>();
    //GameObject *bulletPrefab = Game::getInstance().mainScene->createGameObject();
    //bulletPrefab->addComponent<PlayerBullet>();
  };

  //void update() override;
  //void fixedUpdate() override;
  void setDirection(const glm::vec3 &input) { direction = input; }
  void shooting(bool shooting) {
    isShooting = shooting;
    if (!isShooting) {
      shootingCooldown = 0;
    }
  }

private:
//  ObjectPool bullets;
  glm::vec3 direction = glm::vec3(0.0f);
  int playerHealth = 100;
  float shootingCooldown = 0.0f;
  float reviveCooldown = 0.0f;
  bool isShooting = false;
};
} // namespace BBong
#endif // PLAYER_HPP