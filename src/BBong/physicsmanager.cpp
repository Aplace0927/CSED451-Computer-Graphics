#include "BBong/physicsmanager.hpp"

namespace BBong {
PhysicsManager::PhysicsManager() { start(); }

PhysicsManager::~PhysicsManager() { stop(); }

std::shared_ptr<std::function<void()>>
PhysicsManager::registerHandler(std::function<void()> func) {
  auto ptr = std::make_shared<std::function<void()>>(func);
  std::lock_guard<std::recursive_mutex> lock(fixedUpdateHandlerMutex);
  handlers.push_back(ptr);
  return ptr;
}

void PhysicsManager::unregisterHandler(
    std::shared_ptr<std::function<void()>> ptr) {
  std::lock_guard<std::recursive_mutex> lock(fixedUpdateHandlerMutex);
  handlers.erase(std::remove(handlers.begin(), handlers.end(), ptr),
                 handlers.end());
}

void PhysicsManager::fixedUpdate() {
  std::vector<std::shared_ptr<std::function<void()>>> fixedUpdatesCopy;
  {
    std::lock_guard<std::recursive_mutex> lock(fixedUpdateHandlerMutex);
    fixedUpdatesCopy = handlers; // Create a copy to avoid holding the lock
  }

  if (fixedUpdatesCopy.empty()) {
    return;
  }
  for (auto &handler : fixedUpdatesCopy) {
    if (handler == nullptr) {
      continue;
    }
    (*handler)();
  }
}

void PhysicsManager::start() {
  if (running)
    return;
  running = true;
  loopThread = std::thread([this]() {
    while (running) {
      auto start = std::chrono::high_resolution_clock::now();

      fixedUpdate();

      auto end = std::chrono::high_resolution_clock::now();
      std::chrono::duration<float> elapsed = end - start;
      auto sleepDuration =
          std::chrono::duration<float>(GameConfig::FIXED_DELTATIME) - elapsed;
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
} // namespace PhysicsManager