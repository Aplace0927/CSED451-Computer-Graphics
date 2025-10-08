#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "transform.hpp"
#include "graphicsmanager.hpp"
#include "physicsmanager.hpp"

namespace GameObject {
class Scene : public GameObject {
public:
  Scene() : transform(new Transform::Transform) {
    fixedUpdate_ptr =
        PhysicsManager::PhysicsManager::getInstance().registerHandler(
            []() { fixedUpdate(); });
    update_ptr =
        GraphicsManager::GraphicsManager::getInstance().registerHandler(
            []() { update(); });
    lateUpdate_ptr =
        GraphicsManager::GraphicsManager::getInstance().registerHandler(
            []() { lateUpdate(); });
    renderUpdate_ptr =
        GraphicsManager::GraphicsManager::getInstance().registerHandler(
            []() { renderUpdate(); });
  }
  ~Scene() {
    PhysicsManager::PhysicsManager::getInstance().unregisterHandler(
        fixedUpdate_ptr);
    GraphicsManager::GraphicsManager::getInstance().unregisterHandler(
        update_ptr);
    GraphicsManager::GraphicsManager::getInstance().unregisterHandler(
        lateUpdate_ptr);
    GraphicsManager::GraphicsManager::getInstance().unregisterHandler(
        renderUpdate_ptr);
  }

  Transform::Transform *getSceneGraph() const { return transform; }

private:
  std::shared_ptr<std::function<void()>> update_ptr;
  std::shared_ptr<std::function<void()>> fixedUpdate_ptr;
  std::shared_ptr<std::function<void()>> lateUpdate_ptr;
  std::shared_ptr<std::function<void()>> renderUpdate_ptr;
};
} // namespace GameObject

#endif // OBJECT_HPP