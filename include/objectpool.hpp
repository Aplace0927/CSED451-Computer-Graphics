#include <vector>
#include <memory>

#include "config.hpp"
#include "object.hpp"

namespace ObjectPool
{
    template <typename T>
    class ObjectPool {
    public:
        ObjectPool() {
            pool.reserve(GameConfig::DEFAULT_POOL_SIZE);
            for (int i = 0; i < GameConfig::DEFAULT_POOL_SIZE; ++i) {
                pool.push_back(std::make_unique<T>());
            }
        }
        ObjectPool(int size) {
            pool.reserve(size);
            for (int i = 0; i < size; ++i) {
                pool.push_back(std::make_unique<T>());
            }
        }

        T* acquire() {
            for (auto& obj : pool) {
                if (!obj->active) return obj.get();
            }
            return nullptr;
        }

        void release(T* obj) { obj->reset(); }
    private:
        std::vector<std::unique_ptr<T>> pool;
    };
}