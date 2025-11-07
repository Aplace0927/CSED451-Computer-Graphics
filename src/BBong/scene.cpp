#include "BBong/scene.hpp"

#include <algorithm>
#include <unordered_set>
#include "BBong/physicsmanager.hpp"
#include "BBong/graphicsmanager.hpp"

namespace BBong {

Scene::Scene() {
  fixedUpdate_ptr = PhysicsManager::getInstance().registerHandler(
      [this]() { this->fixedUpdate(); });
  update_ptr = GraphicsManager::getInstance().registerHandler(
      [this]() { this->update(); });
  lateUpdate_ptr = GraphicsManager::getInstance().registerHandler(
      [this]() { this->lateUpdate(); });
  renderUpdate_ptr = GraphicsManager::getInstance().registerHandler(
      [this]() { this->renderUpdate(); });
}

Scene::~Scene() {
  PhysicsManager::getInstance().unregisterHandler(fixedUpdate_ptr);
  GraphicsManager::getInstance().unregisterHandler(update_ptr);
  GraphicsManager::getInstance().unregisterHandler(lateUpdate_ptr);
  GraphicsManager::getInstance().unregisterHandler(renderUpdate_ptr);

  m_gameObjects.clear();
}

GameObject *Scene::createGameObject(Transform *parent) {
  auto newObjectPtr = std::make_unique<GameObject>(parent);
  auto rawPtr = newObjectPtr.get();
  m_gameObjects.push_back(std::move(newObjectPtr));

  return rawPtr;
}

GameObject *Scene::Instantiate(const GameObject &prefab, Transform *parent) {
  GameObject *newGameObject = createGameObject(parent);

  newGameObject->cloneFrom(prefab, parent);

  for (const auto childTransform : prefab.transform->getChildren()) {
    Instantiate(*(childTransform->gameObject), newGameObject->transform);
  }
  return newGameObject;
}

void Scene::destroyGameObject(GameObject *objToDestroy) {
  if (!objToDestroy) {
    return;
  }

  std::vector<GameObject *> objectsToDestroy;
  std::function<void(GameObject *)> collectAll;
  collectAll = [&](GameObject *obj) {
    if (!obj)
      return;
    objectsToDestroy.push_back(obj);
    for (const auto childTransform : obj->transform->getChildren()) {
      if (childTransform && childTransform->gameObject) {
        collectAll(childTransform->gameObject);
      }
    }
  };

  collectAll(objToDestroy);

  std::unordered_set<GameObject *> destroySet(objectsToDestroy.begin(),
                                              objectsToDestroy.end());

  std::lock_guard<std::recursive_mutex> lock(sceneMutex);
  m_gameObjects.erase(
      std::remove_if(m_gameObjects.begin(), m_gameObjects.end(),
                     [&](const std::shared_ptr<GameObject> &ptr) {
                       return destroySet.count(ptr.get()) > 0;
                     }),
      m_gameObjects.end());
}

void Scene::fixedUpdate() {
  std::vector<std::shared_ptr<GameObject>> gameObjectsCopy;
  {
    std::lock_guard<std::recursive_mutex> lock(sceneMutex);
    gameObjectsCopy = m_gameObjects; // Create a copy to avoid holding the lock
  }
  for (const auto &objPtr : gameObjectsCopy) {
    if (objPtr && objPtr->transform->getParent() == nullptr) {
      objPtr->fixedUpdate();
    }
  }
}

void Scene::update() {
  std::vector<std::shared_ptr<GameObject>> gameObjectsCopy;
  {
    std::lock_guard<std::recursive_mutex> lock(sceneMutex);
    gameObjectsCopy = m_gameObjects; // Create a copy to avoid holding the lock
  }
  for (const auto &objPtr : gameObjectsCopy) {
    if (objPtr && objPtr->transform->getParent() == nullptr) {
      objPtr->update();
    }
  }
}

void Scene::lateUpdate() {
  std::vector<std::shared_ptr<GameObject>> gameObjectsCopy;
  {
    std::lock_guard<std::recursive_mutex> lock(sceneMutex);
    gameObjectsCopy = m_gameObjects; // Create a copy to avoid holding the lock
  }
  for (const auto &objPtr : gameObjectsCopy) {
    if (objPtr && objPtr->transform->getParent() == nullptr) {
      objPtr->lateUpdate();
    }
  }
}

void Scene::renderUpdate() {
  std::vector<std::shared_ptr<GameObject>> gameObjectsCopy;
  {
    std::lock_guard<std::recursive_mutex> lock(sceneMutex);
    gameObjectsCopy = m_gameObjects; // Create a copy to avoid holding the lock
  }
  for (const auto &objPtr : gameObjectsCopy) {
    if (objPtr && objPtr->transform->getParent() == nullptr) {
      objPtr->renderUpdate();
    }
  }
}
} // namespace BBong