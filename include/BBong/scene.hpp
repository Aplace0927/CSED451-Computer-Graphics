#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <memory>
#include <functional>

#include "BBong/physicsmanager.hpp"
#include "BBong/graphicsmanager.hpp"
#include "BBong/gameobject.hpp"
#include "BBong/transform.hpp"

namespace BBong {
class Scene {
private:
  std::vector<GameObject *> m_gameObjects;

  std::shared_ptr<std::function<void()>> fixedUpdate_ptr;
  std::shared_ptr<std::function<void()>> update_ptr;
  std::shared_ptr<std::function<void()>> lateUpdate_ptr;
  std::shared_ptr<std::function<void()>> renderUpdate_ptr;

public:
  Scene() {
    fixedUpdate_ptr = PhysicsManager::getInstance().registerHandler(
        [this]() { this->fixedUpdate(); });
    update_ptr = GraphicsManager::getInstance().registerHandler(
        [this]() { this->update(); });
    lateUpdate_ptr = GraphicsManager::getInstance().registerHandler(
        [this]() { this->lateUpdate(); });
    renderUpdate_ptr = GraphicsManager::getInstance().registerHandler(
        [this]() { this->renderUpdate(); });
  }
  ~Scene() {
    PhysicsManager::getInstance().unregisterHandler(
        fixedUpdate_ptr);
    GraphicsManager::getInstance().unregisterHandler(update_ptr);
    GraphicsManager::getInstance().unregisterHandler(
        lateUpdate_ptr);
    GraphicsManager::getInstance().unregisterHandler(
        renderUpdate_ptr);

    for (auto *obj : m_gameObjects) {
      delete obj;
    }
    m_gameObjects.clear();
  }

  Scene(const Scene &) = delete;
  Scene &operator=(const Scene &) = delete;

  GameObject *createGameObject(Transform *parent = nullptr) {
    GameObject *newObject = new GameObject(parent);
    if (!parent)
      m_gameObjects.push_back(newObject);
    return newObject;
  }

  GameObject *Instantiate(const GameObject &prefab,
                          Transform *parent = nullptr) {
    GameObject *newGameObject = createGameObject(parent);

    newGameObject->cloneFrom(prefab, parent);

    for (const auto childTransform : prefab.transform->getChildren()) {
      Instantiate(*(childTransform->gameObject), newGameObject->transform);
    }
    return newGameObject;
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
} // namespace BBong

#endif // SCENE_HPP