#ifndef OBJECTPOOL_HPP
#define OBJECTPOOL_HPP

#include <memory>
#include <vector>

#include "config.hpp"
#include "object.hpp"

namespace ObjectPool {
template <typename T> class ObjectPool {
public:
  ObjectPool() {
    pool.reserve(GameConfig::DEFAULT_POOL_SIZE);
    for (int i = 0; i < GameConfig::DEFAULT_POOL_SIZE; ++i) {
      pool.push_back(new T());
    }
  }
  ObjectPool(int size) {
    pool.reserve(size);
    for (int i = 0; i < size; ++i) {
      pool.push_back(new T());
    }
  }

  T *acquire() {
    if (pool.empty())
      return new T();
    T *obj = pool.back();
    pool.pop_back();
    return obj;
  }

  void release(T *obj) {
    obj->deactivate();
    pool.push_back(obj);
  }

private:
  std::vector<T *> pool;
};
} // namespace ObjectPool

#endif // OBJECTPOOL_HPP