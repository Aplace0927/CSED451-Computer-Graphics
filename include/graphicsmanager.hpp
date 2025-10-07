#ifndef GRAPHICSMANAGER_HPP
#define GRAPHICSMANAGER_HPP

#include <vector>
#include <memory>
#include <functional>
#include <mutex>
#include <algorithm>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <chrono>
#include <glm/glm.hpp>

#include "singleton.hpp"
#include "config.hpp"

namespace GraphicsManager {
typedef std::function<void(float)> GraphicsManagerFunc;

class GraphicsManager : public Singleton::Singleton<GraphicsManager> {
private:
  std::chrono::high_resolution_clock::time_point lastFrame;
  GraphicsManager(const GraphicsManager &) = delete;
  GraphicsManager &operator=(const GraphicsManager &) = delete;

  void resetCamera() const;
  void applyCameraShake() const;

  std::vector<std::shared_ptr<GraphicsManagerFunc>> handlers;
  std::recursive_mutex updateHandlerMutex;
  bool shaking = false;
  float shakeDuration = 0.0f;
  float shakeTimer = 0.0f;
  float shakeMagnitude = 0.0f;
  float shakeSpeed = 0.0f;

public:
  GraphicsManager() { lastFrame = std::chrono::high_resolution_clock::now(); };
  ~GraphicsManager() = default;

  std::shared_ptr<GraphicsManagerFunc>
  registerHandler(GraphicsManagerFunc func);
  void unregisterHandler(std::shared_ptr<GraphicsManagerFunc> ptr);

  void startCameraShake(float duration, float magnitude, float speed);
  void reshape(int width, int height);
  void update();
};
} // namespace GraphicsManager

#endif // GRAPHICSMANAGER_HPP