#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "transform.hpp"
#include "graphicsmanager.hpp"
#include "physicsmanager.hpp"

namespace EngineManager {
class Scene {
private:
  std::vector<GameObject::GameObject *> m_gameObjects;

  std::shared_ptr<std::function<void()>> update_ptr;
  std::shared_ptr<std::function<void()>> fixedUpdate_ptr;
  std::shared_ptr<std::function<void()>> lateUpdate_ptr;
  std::shared_ptr<std::function<void()>> renderUpdate_ptr;

public:
  explicit Scene() {
    fixedUpdate_ptr =
        EngineManager::PhysicsManager::getInstance().registerHandler(
            [this]() { this->fixedUpdate(); });
    update_ptr = EngineManager::GraphicsManager::getInstance().registerHandler(
        [this]() { this->update(); });
    lateUpdate_ptr =
        EngineManager::GraphicsManager::getInstance().registerHandler(
            [this]() { this->lateUpdate(); });
    renderUpdate_ptr =
        EngineManager::GraphicsManager::getInstance().registerHandler(
            [this]() { this->renderUpdate(); });
  }
  ~Scene() {
    EngineManager::PhysicsManager::getInstance().unregisterHandler(
        fixedUpdate_ptr);
    EngineManager::GraphicsManager::getInstance().unregisterHandler(update_ptr);
    EngineManager::GraphicsManager::getInstance().unregisterHandler(
        lateUpdate_ptr);
    EngineManager::GraphicsManager::getInstance().unregisterHandler(
        renderUpdate_ptr);

    for (auto *obj : m_gameObjects) {
      delete obj;
    }
    m_gameObjects.clear();
  }

  Scene(const Scene &) = delete;
  Scene &operator=(const Scene &) = delete;

  GameObject::GameObject *CreateGameObject(Component::Transform *parent = nullptr) {
    GameObject::GameObject *newObject = new GameObject::GameObject(parent);
    if (!parent)
        m_gameObjects.push_back(newObject);
    return newObject;
  }

private:
  void fixedUpdate() {
    for (auto *obj : m_gameObjects) {
      obj->fixedUpdate();
    }
  }
  void update() {
    for (auto *obj : m_gameObjects) {
      obj->update();
    }
  }
  void lateUpdate() {
    for (auto *obj : m_gameObjects) {
      obj->lateUpdate();
    }
  }
  void renderUpdate() {
    for (auto *obj : m_gameObjects) {
      obj->renderUpdate();
    }
  }
};
} // namespace EngineManager

#endif // OBJECT_HPP