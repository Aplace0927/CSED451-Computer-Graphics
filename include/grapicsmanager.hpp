#ifndef GRAPICSMANAGER_HPP
#define GRAPICSMANAGER_HPP

#include <glm/glm.hpp>
#include <vector>

#include "singleton.hpp"

namespace GraphicsManager {
    class GraphicsManager : public Singleton::Singleton<GraphicsManager> {
    private:
        GraphicsManager(const GraphicsManager&) = delete;
        GraphicsManager& operator=(const GraphicsManager&) = delete;

        std::vector<std::function<void()>> handlers;

    public:
        void registerHandler(std::function<void()> func) {
            handlers.push_back(func);
        }
        void update() {
            for (auto& handler : handlers) {
                handler();
			}
        };
    };
}

#endif // GRAPICSMANAGER_HPP