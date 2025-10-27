#ifndef PHYSICSMANAGER_HPP
#define PHYSICSMANAGER_HPP

#include <vector>
#include <functional>
#include <thread>
#include <memory>
#include <atomic>
#include <chrono>
#include <mutex>

#include "BBong/singleton.hpp"
#include "config.hpp"

namespace BBong {
class PhysicsManager : public Singleton<PhysicsManager> {
public:
  PhysicsManager();
  ~PhysicsManager();

  std::shared_ptr<std::function<void()>>
  registerHandler(std::function<void()> func);
  void unregisterHandler(std::shared_ptr<std::function<void()>> ptr);

private:
  PhysicsManager(const PhysicsManager &) = delete;
  PhysicsManager &operator=(const PhysicsManager &) = delete;

  std::vector<std::shared_ptr<std::function<void()>>> handlers;

  std::atomic<bool> running{false};
  std::thread loopThread;
  std::recursive_mutex fixedUpdateHandlerMutex;

  void start();
  void stop();
  void fixedUpdate();
};
}; // namespace EngineManager

#endif // PHYSICSMANAGER_HPP