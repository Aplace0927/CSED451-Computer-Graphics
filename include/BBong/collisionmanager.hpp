#ifndef COLLISIONMANAGER_HPP
#define COLLISIONMANAGER_HPP

#include <vector>
#include <mutex>
#include <cstdint>
#include <array>
#include "BBong/singleton.hpp"
#include "config.hpp"

namespace BBong {

class Collider2D;
class Collider3D;

class CollisionManager : public Singleton<CollisionManager> {
public:
  CollisionManager() = default;
  ~CollisionManager() = default;

  void registerCollider3D(Collider3D *collider);
  void unregisterCollider3D(Collider3D *collider);

  void checkCollisions3D();

private:
  CollisionManager(const CollisionManager &) = delete;
  CollisionManager &operator=(const CollisionManager &) = delete;

  std::array<std::vector<Collider3D *>, GameConfig::MAX_LAYERS> m_collidersByLayer;
  std::recursive_mutex m_colliderMutex;
};
}; // namespace BBong

#endif // COLLISIONMANAGER_HPP