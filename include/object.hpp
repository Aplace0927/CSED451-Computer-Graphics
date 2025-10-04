#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "shape.hpp"
#include "boundingbox.hpp"
#include "graphicsmanager.hpp"
#include "physicsmanager.hpp"

namespace Object {
template <typename T, typename C> class Object {
public:
  Object(const T &_position, const SceneGraph::SceneGraph<T, C> *_scenegraph,
         std::function<void()> releaseFunc = nullptr)
      : scenegraph(_scenegraph), releaseFunc(releaseFunc) {
    // Update to actual position (also initializes bounding box)
    active = true;
    boundingBox = scenegraph->getBoundingBox();
    update_ptr =
        GraphicsManager::GraphicsManager::getInstance().registerHandler(
            [this](float time) { this->update(time); });
    fixedUpdate_ptr =
        PhysicsManager::PhysicsManager::getInstance().registerHandler(
            [this]() { this->fixedUpdate(); });
  }
  ~Object() {
    GraphicsManager::GraphicsManager::getInstance().unregisterHandler(
        update_ptr);
    PhysicsManager::PhysicsManager::getInstance().unregisterHandler(
        fixedUpdate_ptr);
  }

  void setPosition(const T &position) {
    // Move by the difference between current center and new position
    boundingBox = scenegraph.move(position - shape.getCenter());
  }

  void move(const T &displacement) { boundingBox = scenegraph.move(displacement); }

  void rotate(const T &angles, const T &pivot) {
    boundingBox = shape.rotate(angles, pivot);
  }

  T getCenter() const { return shape.getCenter(); }

  void draw(time_t currentTime) {
    scenegraph->draw(currentTime);
    // #ifdef BOUNDING_BOX_DEBUG
    // boundingBox.draw();
    // #endif
  }

  bool getStatus() const { return active; }
  void setStatus(bool state) { active = state; }

  std::function<bool(const BoundingBox::BoundingBox<T> &)>
  getBoundingBoxCollisionFunction() {
    return [this](const BoundingBox::BoundingBox<T> &other) {
      if (!this->active) {
        return false;
      }
      return this->boundingBox & other;
    };
  }

  void setReleaseFunction(std::function<void()> func) { releaseFunc = func; }

  void callReleaseFunction() {
    if (releaseFunc != nullptr) {
      releaseFunc();
    }
  }

  SceneGraph::SceneGraph<T, C>* getSceneGraph() const { return scenegraph; }

  BoundingBox::BoundingBox<T> getBoundingBox() const { return boundingBox; }

  virtual void update(float time);
  virtual void fixedUpdate();

private:
  bool active;
  SceneGraph::SceneGraph<T, C>* scenegraph;
  BoundingBox::BoundingBox<T> boundingBox;
  std::shared_ptr<std::function<void(float)>> update_ptr;
  std::shared_ptr<std::function<void()>> fixedUpdate_ptr;
  std::function<void()> releaseFunc;
};

template <typename T, typename C> void Object<T, C>::update(float time) {
  // Default implementation does nothing
}

template <typename T, typename C> void Object<T, C>::fixedUpdate() {
  // Default implementation does nothing
}
} // namespace Object

#endif // OBJECT_HPP