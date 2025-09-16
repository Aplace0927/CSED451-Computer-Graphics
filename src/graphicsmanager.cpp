#include "graphicsmanager.hpp"
#include <algorithm>
#include <GL/glew.h>
#include <GL/freeglut.h>

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
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        for (auto& handler : handlers) {
            (*handler)();
        }

        glutSwapBuffers();
        glutPostRedisplay();
    }
}