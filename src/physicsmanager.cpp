#include "PhysicsManager.hpp"
#include <chrono>

namespace PhysicsManager {
    PhysicsManager::PhysicsManager() {
        start();
    }
    
    PhysicsManager::~PhysicsManager() {
        stop();
    }

    std::shared_ptr<std::function<void()>> PhysicsManager::registerHandler(std::function<void()> func) {
        auto ptr = std::make_shared<std::function<void()>>(func);
        handlers.push_back(ptr);
        return ptr;
    }

    void PhysicsManager::unregisterHandler(std::shared_ptr<std::function<void()>> ptr) {
        handlers.erase(
            std::remove(handlers.begin(), handlers.end(), ptr),
            handlers.end()
        );
    }

    void PhysicsManager::fixedUpdate() {
        for (auto& handler : handlers) {
            (*handler)();
        }
    }

    void PhysicsManager::start() {
        if (running) return; // 이미 실행 중이면 무시
        running = true;
        loopThread = std::thread([this]() {
            while (running) {
                auto start = std::chrono::high_resolution_clock::now();

                fixedUpdate();

                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<float> elapsed = end - start;
                auto sleepDuration = std::chrono::duration<float>(fixedtime) - elapsed;
                if (sleepDuration.count() > 0)
                    std::this_thread::sleep_for(sleepDuration);
            }
            });
    }

    void PhysicsManager::stop() {
        running = false;
        if (loopThread.joinable()) {
            loopThread.join();
        }
    }
}