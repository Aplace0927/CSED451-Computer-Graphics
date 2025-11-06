#ifndef OBJECTPOOL_HPP
#define OBJECTPOOL_HPP

#include <vector>
#include <memory>

#include "config.hpp"
#include "game.hpp"
#include "BBong/gameobject.hpp"
#include "BBong/transform.hpp"

namespace BBong {
class ObjectPool {
public:
  explicit ObjectPool(GameObject &prefabObj, Transform *parent = nullptr,
                      int size = GameConfig::DEFAULT_POOL_SIZE)
      : prefab(&prefabObj), parent(parent) {
    pool.reserve(size);
    for (int i = 0; i < size; ++i) {
      auto obj = Game::getInstance().mainScene->Instantiate(*prefab, parent);
      obj->setActive(false);
      pool.push_back(obj);
    }
  }

  ObjectPool(const ObjectPool &) = delete;
  ObjectPool &operator=(const ObjectPool &) = delete;
  ~ObjectPool() = default;

  GameObject *acquire() {
    if (pool.empty()) {
      auto obj = Game::getInstance().mainScene->Instantiate(*prefab, parent);
      obj->setActive(true);
      return obj;
    } else {
      GameObject *obj = pool.back();
      pool.pop_back();
      obj->setActive(true);
      return obj;
    }
  }

  void release(GameObject *obj) {
    if (!obj)
      return;
    obj->setActive(false);
    pool.push_back(obj);
  }

private:
  std::vector<GameObject *> pool;
  GameObject *prefab;
  Transform *parent;
};
} // namespace BBong

#endif // OBJECTPOOL_HPP