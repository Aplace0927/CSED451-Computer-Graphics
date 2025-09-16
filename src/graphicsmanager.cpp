#include "graphicsmanager.hpp"

namespace GraphicsManager {
    std::shared_ptr<std::function<void(time_t)>> GraphicsManager::registerHandler(std::function<void(time_t)> func) {
        auto ptr = std::make_shared<std::function<void(time_t)>>(func);
        handlers.push_back(ptr);
        return ptr;
    }

    void GraphicsManager::unregisterHandler(std::shared_ptr<std::function<void(time_t)>> ptr) {
        handlers.erase(
            std::remove(handlers.begin(), handlers.end(), ptr),
            handlers.end()
        );
    }

    void GraphicsManager::update() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        time_t current_time = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
        ).count();

        if (handlers.empty()) {
            return;
        }
        for (auto& handler : handlers) {
            if (handler == nullptr) {
                throw std::runtime_error("Null handler in PhysicsManager");
                continue;
            }
            (*handler)(current_time);
        }

        glutSwapBuffers();
        glutPostRedisplay();
    }
}