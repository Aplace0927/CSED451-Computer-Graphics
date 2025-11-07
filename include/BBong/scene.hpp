#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <memory>
#include <functional>
#include <mutex>

#include "BBong/gameobject.hpp"
#include "BBong/transform.hpp"

namespace BBong {
class Scene {
public:
  Scene();
  ~Scene();

  Scene(const Scene &) = delete;
  Scene &operator=(const Scene &) = delete;

  GameObject *createGameObject(Transform *parent = nullptr);
  GameObject *Instantiate(const GameObject &prefab,
                          Transform *parent = nullptr);
  void destroyGameObject(GameObject *objToDestroy);

private:
  void fixedUpdate();
  void update();
  void lateUpdate();
  void renderUpdate();

  std::vector<std::shared_ptr<GameObject>> m_gameObjects;

  std::shared_ptr<std::function<void()>> fixedUpdate_ptr;
  std::shared_ptr<std::function<void()>> update_ptr;
  std::shared_ptr<std::function<void()>> lateUpdate_ptr;
  std::shared_ptr<std::function<void()>> renderUpdate_ptr;

  std::recursive_mutex sceneMutex;
};
} // namespace BBong

#endif // SCENE_HPP