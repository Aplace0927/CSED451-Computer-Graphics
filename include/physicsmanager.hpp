#ifndef PHYSICSMANAGER_HPP
#define PHYSICSMANAGER_HPP

#include <vector>
#include <functional>
#include <thread>
#include <memory>
#include <atomic>
#include <chrono>
#include <mutex>

#include "singleton.hpp"
#include "config.hpp"

namespace PhysicsManager {

class PhysicsManager : public Singleton::Singleton<PhysicsManager> {

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

} // namespace PhysicsManager

#endif // PHYSICSMANAGER_HPP