#ifndef BBONG_GAMEOBJECT_HPP
#define BBONG_GAMEOBJECT_HPP

#include <vector>
#include <memory>
#include <type_traits>
#include "BBong/transform.hpp"
#include "BBong/component.hpp"

namespace BBong {
class Scene;
class CollisionManager;
class Collider3D;

class GameObject {
public:
  Transform *transform;

private:
  bool m_isActive;
  std::vector<std::unique_ptr<Component>> m_components;

public:
  explicit GameObject(Transform *parent = nullptr);

  ~GameObject() = default;
  GameObject(const GameObject &) = delete;
  GameObject &operator=(const GameObject &) = delete;

  template <typename T> T *addComponent() {
    static_assert(std::is_base_of_v<Component, T>,
                  "T must be a class derived from BBong::Component");

    auto newComponent = std::make_unique<T>(this);
    T *rawPtr = newComponent.get();
    m_components.push_back(std::move(newComponent));
    return rawPtr;
  }
  template <typename T> T *getComponent() {
    static_assert(std::is_base_of_v<Component, T>,
                  "T must be a class derived from BBong::Component");

    for (const auto &comp : m_components) {
      T *ptr = dynamic_cast<T *>(comp.get());
      if (ptr != nullptr) {
        return ptr;
      }
    }
    return nullptr;
  }

  bool getActive() const { return m_isActive; }
  void setActive(bool state) { m_isActive = state; }

private:
  friend class Scene;
  friend class CollisionManager;

  void cloneComponentsFrom(const GameObject &other);
  void cloneFrom(const GameObject &other, Transform *parent);

  void fixedUpdate();
  void collision3D(Collider3D *collider);
  void update();
  void lateUpdate();
  void renderUpdate();
};
} // namespace BBong
#endif // BBONG_GAMEOBJECT_HPP