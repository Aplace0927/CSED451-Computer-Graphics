#include <vector>
#include <memory>

#include "object.hpp"

namespace ObjectPool
{
    template <typename T>
    class ObjectPool {
    private:
        std::vector<std::unique_ptr<T>> pool;

    public:
        ObjectPool() {
        }
        ObjectPool(int size) {
        }

        T* acquire() {
            for (auto& obj : pool) {
                if (!obj->active) return obj.get();
            }
            return nullptr;
        }

        void release(T* obj) { obj->reset(); }
    };
}