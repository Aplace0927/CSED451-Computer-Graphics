#ifndef OBJECTPOOL_HPP
#define OBJECTPOOL_HPP

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
                // pool.push_back(std::make_unique<T>());
                pool.push_back(new T());
            }
        }
        ObjectPool(int size) {
            pool.reserve(size);
            for (int i = 0; i < size; ++i) {
                // pool.push_back(std::make_unique<T>());
                pool.push_back(new T());
            }
        }

        T* acquire() {
            if (pool.empty()) {
                pool.push_back(new T());
            }
            T* obj = pool.back();
            pool.pop_back();
            return obj;
            //for (auto& obj : pool) {
            //    if (!obj->getStatus()) {
            //        return obj;
            //    }
            //}
            //return nullptr;
        }

        void release(T* obj) { obj->deactivate(); pool.push_back(obj); }
        // std::vector<std::unique_ptr<T>> pool;
        std::vector<T*> pool;
    private:
        
    };
}

#endif // OBJECTPOOL_HPP