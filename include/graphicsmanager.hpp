#ifndef GRAPHICSMANAGER_HPP
#define GRAPHICSMANAGER_HPP

#include <GL/freeglut.h>
#include <GL/glew.h>
#include <algorithm>
#include <chrono>
#include <functional>
#include <glm/glm.hpp>
#include <memory>
#include <vector>

#include "config.hpp"
#include "singleton.hpp"

namespace GraphicsManager {
class GraphicsManager : public Singleton::Singleton<GraphicsManager> {
private:
  std::chrono::high_resolution_clock::time_point lastFrame;
  GraphicsManager(const GraphicsManager &) = delete;
  GraphicsManager &operator=(const GraphicsManager &) = delete;

  void resetCamera() const;
  void applyCameraShake() const;

  std::vector<std::shared_ptr<std::function<void(float)>>> handlers;
  bool shaking = false;
  float shakeDuration = 0.0f;
  float shakeTimer = 0.0f;
  float shakeMagnitude = 0.0f;
  float shakeSpeed = 0.0f;

public:
  GraphicsManager() { lastFrame = std::chrono::high_resolution_clock::now(); };
  ~GraphicsManager() = default;

  std::shared_ptr<std::function<void(float)>>
  registerHandler(std::function<void(float)> func);
  void unregisterHandler(std::shared_ptr<std::function<void(float)>> ptr);

  void startCameraShake(float duration, float magnitude, float speed);
  void reshape(int width, int height);
  void update();
};
} // namespace GraphicsManager

#endif // GRAPHICSMANAGER_HPP