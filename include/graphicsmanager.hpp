#ifndef GRAPHICSMANAGER_HPP
#define GRAPHICSMANAGER_HPP

#include <vector>
#include <memory>
#include <functional>
#include <algorithm>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "singleton.hpp"

namespace GraphicsManager {
    class GraphicsManager : public Singleton::Singleton<GraphicsManager> {
    private:
        GraphicsManager(const GraphicsManager&) = delete;
        GraphicsManager& operator=(const GraphicsManager&) = delete;

        std::vector<std::shared_ptr<std::function<void()>>> handlers;

    public:
        GraphicsManager() = default;
        ~GraphicsManager() = default;

        std::shared_ptr<std::function<void()>> registerHandler(std::function<void()> func);
        void unregisterHandler(std::shared_ptr<std::function<void()>> ptr);
        void update();
    };
}

#endif // GRAPHICSMANAGER_HPP