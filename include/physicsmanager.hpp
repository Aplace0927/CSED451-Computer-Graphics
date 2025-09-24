#ifndef PHYSICSMANAGER_HPP
#define PHYSICSMANAGER_HPP

#include <vector>
#include <functional>
#include <thread>
#include <memory>
#include <atomic>
#include "singleton.hpp"

namespace PhysicsManager {

class PhysicsManager : public Singleton::Singleton<PhysicsManager> {
private:
  PhysicsManager(const PhysicsManager &) = delete;
  PhysicsManager &operator=(const PhysicsManager &) = delete;

  std::vector<std::shared_ptr<std::function<void()>>> handlers;

  std::atomic<bool> running{false};
  std::thread loopThread;

private:
  void start();
  void stop();
  void fixedUpdate();

public:
  PhysicsManager();
  ~PhysicsManager();

  std::shared_ptr<std::function<void()>>
  registerHandler(std::function<void()> func);
  void unregisterHandler(std::shared_ptr<std::function<void()>> ptr);
};

} // namespace PhysicsManager

#endif // PHYSICSMANAGER_HPP