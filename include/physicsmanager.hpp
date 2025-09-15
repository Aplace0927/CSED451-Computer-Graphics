#ifndef PHYSICSMANAGER_HPP
#define PHYSICSMANAGER_HPP

#include <glm/glm.hpp>
#include <vector>

#include "singleton.hpp"

namespace PhysicsManager {
    class PhysicsManager : public Singleton::Singleton<PhysicsManager> {
    private:
        PhysicsManager(const PhysicsManager&) = delete;
        PhysicsManager& operator=(const PhysicsManager&) = delete;

        std::vector<std::function<void()>> handlers;

    public:
        void registerHandler(std::function<void()> func) {
            handlers.push_back(func);
        }
        void fixedUpdate() {
            for (auto& handler : handlers) {
                handler();
            };
        };
    };
}

#endif // PHYSICSMANAGER_HPP