#include "graphicsmanager.hpp"

namespace GraphicsManager {
    std::shared_ptr<std::function<void(float)>> GraphicsManager::registerHandler(std::function<void(float)> func) {
        auto ptr = std::make_shared<std::function<void(float)>>(func);
        handlers.push_back(ptr);
        return ptr;
    }

    void GraphicsManager::unregisterHandler(std::shared_ptr<std::function<void(float)>> ptr) {
        handlers.erase(
            std::remove(handlers.begin(), handlers.end(), ptr),
            handlers.end()
        );
    }

    void GraphicsManager::update() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        auto now = std::chrono::high_resolution_clock::now();
        float deltaTime = std::chrono::duration<float>(now - lastFrame).count();
        lastFrame = now;

        if (handlers.empty()) {
            return;
        }
        for (auto& handler : handlers) {
            if (handler == nullptr) {
                throw std::runtime_error("Null handler in GraphicsManager");
                continue;
            }
            (*handler)(deltaTime);
        }

        if (shaking) {
            shakeTimer += deltaTime;
            if (shakeTimer >= shakeDuration) {
                shaking = false;
            }
            else {
                applyCameraShake();
            }
        }

        glutSwapBuffers();
        glutPostRedisplay();
    }

    void GraphicsManager::applyCameraShake() const {
        float offsetX = sin(shakeTimer * shakeSpeed) * shakeMagnitude;
        float offsetY = cos(shakeTimer * shakeSpeed * 1.3f) * shakeMagnitude;

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        float halfWidth = static_cast<float>(GameConfig::WINDOW_WIDTH) / 2;
        float halfHeight = static_cast<float>(GameConfig::WINDOW_HEIGHT) / 2;
        gluOrtho2D(-halfWidth, halfWidth, -halfHeight, halfHeight);

        glTranslatef(-offsetX, -offsetY, 0.0f);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }

    void GraphicsManager::startCameraShake(float duration, float magnitude, float speed) {
        shakeDuration = duration;
        shakeMagnitude = magnitude;
        shakeSpeed = speed;
        shakeTimer = 0.0f;
        shaking = true;
	}

    void GraphicsManager::reshape(int width, int height) {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        
        float halfWidth = static_cast<float>(GameConfig::WINDOW_WIDTH) / 2;
        float halfHeight = static_cast<float>(GameConfig::WINDOW_HEIGHT) / 2;
        gluOrtho2D(-halfWidth, halfWidth, -halfHeight, halfHeight);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        float originalAspect = static_cast<float>(GameConfig::WINDOW_WIDTH) / GameConfig::WINDOW_HEIGHT;
        float aspect = static_cast<float>(width) / height;

        if (aspect > originalAspect) {
            int newWidth = originalAspect * height;
            int xOffset = (width - newWidth) / 2;
            glViewport(xOffset, 0, newWidth, height);
        }
        else {
            int newHeight = width / originalAspect;
            int yOffset = (height - newHeight) / 2;
            glViewport(0, yOffset, width, newHeight);
        }
    }
}