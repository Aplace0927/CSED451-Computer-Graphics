#include "graphicsmanager.hpp"
#include <algorithm>

namespace GraphicsManager {
    std::shared_ptr<std::function<void()>> GraphicsManager::registerHandler(std::function<void()> func) {
        auto ptr = std::make_shared<std::function<void()>>(func);
        handlers.push_back(ptr);
        return ptr;
    }

    void GraphicsManager::unregisterHandler(std::shared_ptr<std::function<void()>> ptr) {
        handlers.erase(
            std::remove(handlers.begin(), handlers.end(), ptr),
            handlers.end()
        );
    }

    void GraphicsManager::update() {
        for (auto& handler : handlers) {
            (*handler)();
        }
    }
}