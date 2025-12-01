#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <memory>
#include <vector>
#include <cmath>

#include "BBong/gameobject.hpp"
#include "BBong/renderer3d.hpp"
#include "BBong/collider3d.hpp"
#include "BBong/collisionmanager.hpp"
#include "BBong/component.hpp"
#include "BBong/objloader.hpp"
#include "BBong/inputmanager.hpp"
#include "BBong/texturemanager.hpp"
#include "BBong/camera.hpp"
#include "objectpool.hpp"
#include "config.hpp"
#include "bullet.hpp"

namespace BBong {
class Player : public ClonableComponent<Player> {
public:
  explicit Player(GameObject *owner);
  Player(const Player &other);
  ~Player() override;

  void update() override;
  void fixedUpdate() override;
  void collision3D(Collider3D *collider) override;

private:
  static GameObject *createBulletPrefab();

  std::shared_ptr<ObjectPool> bullets;
  glm::vec3 animateViewDirection = glm::vec3(0.0f);
  glm::vec3 direction = glm::vec3(0.0f);
  GameObject *shootingPoint;
  GameObject *healthGemOrigin;
  MeshRenderer3D *meshRenderer = nullptr;
  std::vector<GameObject *> healthGems;
  int playerHealth = 10;
  float shootingCooldown = 0.0f;
  float reviveCooldown = 0.0f;
  float speed = 100.0f;
  bool isShooting = false;
  bool isLive = true;
};
} // namespace BBong
#endif // PLAYER_HPP