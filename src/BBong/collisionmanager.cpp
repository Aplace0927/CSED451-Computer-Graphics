#include "BBong/collisionmanager.hpp"

#include <bit>
#include "BBong/collider3d.hpp"
#include "BBong/gameobject.hpp"
#include "config.hpp"

namespace BBong {

void CollisionManager::registerCollider3D(Collider3D *collider) {
  if (collider == nullptr)
    return;

  std::lock_guard<std::recursive_mutex> lock(m_colliderMutex);
  uint8_t layer = collider->getLayer();

  if (layer != 0 && (layer & (layer - 1)) != 0) {
    std::cout << "Warning: Collider registered with multiple layers " << layer
              << " Enforcing single layer rule." << std::endl;
    layer = layer & -layer;
  }

  if (layer != GameConfig::CollisionLayer::NONE)
    m_collidersByLayer[Utility::findFirstSetBit_Loop(layer)].push_back(
        collider);
}

void CollisionManager::unregisterCollider3D(Collider3D *collider) {
  if (collider == nullptr)
    return;

  uint8_t layer = collider->getLayer();

  if (layer == GameConfig::CollisionLayer::NONE)
    return;

  unsigned int layerIndex = Utility::findFirstSetBit_Loop(layer);

  std::lock_guard<std::recursive_mutex> lock(m_colliderMutex);

  std::vector<Collider3D *> &layerVec = m_collidersByLayer[layerIndex];
  layerVec.erase(std::remove(layerVec.begin(), layerVec.end(), collider),
                 layerVec.end());
}

void CollisionManager::checkCollisions3D() {
  std::array<std::vector<Collider3D *>, GameConfig::MAX_LAYERS> collidersCopy;
  {
    std::lock_guard<std::recursive_mutex> lock(m_colliderMutex);
    collidersCopy = m_collidersByLayer;
  }

  for (size_t i = 0; i < GameConfig::MAX_LAYERS; ++i) {
    for (size_t j = 0; j < i; ++j) {
      if (GameConfig::COLLISION_MATRIX[i][j] == 0) {
        continue;
      }
      if (GameConfig::COLLISION_MATRIX[i][j] == 2) {
        continue;
      }

      std::vector<Collider3D *> &collidersA = collidersCopy[i];
      std::vector<Collider3D *> &collidersB = collidersCopy[j];

      if (collidersA.empty() || collidersB.empty()) {
        continue;
      }

      for (Collider3D *a : collidersA) {
        if (a == nullptr)
          continue;

        for (Collider3D *b : collidersB) {
          if (b == nullptr)
            continue;
          if (a->intersects(b)) {
            a->gameObject->collision3D(b);
            b->gameObject->collision3D(a);
          }
        }
      }
    }
    if (GameConfig::COLLISION_MATRIX[i][i] == 0) {
      continue;
    }

    std::vector<Collider3D *> &collidersInLayer = collidersCopy[i];
    if (collidersInLayer.size() < 2)
      continue;

    for (size_t k = 0; k < collidersInLayer.size(); ++k) {
      Collider3D *a = collidersInLayer[k];
      if (a == nullptr)
        continue;

      for (size_t l = k + 1; l < collidersInLayer.size(); ++l) {
        Collider3D *b = collidersInLayer[l];
        if (b == nullptr)
          continue;

        if (a->intersects(b)) {
          a->gameObject->collision3D(b);
          b->gameObject->collision3D(a);
        }
      }
    }
  }
}
} // namespace BBong