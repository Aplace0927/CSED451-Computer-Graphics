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
#include <glm/gtc/type_ptr.hpp>

#include "BBong/singleton.hpp"
#include "config.hpp"
#include "BBong/shadermanager.hpp"

namespace BBong {
typedef std::function<void()> GraphicsManagerFunc;

class GraphicsManager : public Singleton<GraphicsManager> {
private:
  std::chrono::high_resolution_clock::time_point lastFrame;
  GraphicsManager(const GraphicsManager &) = delete;
  GraphicsManager &operator=(const GraphicsManager &) = delete;

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

  std::shared_ptr<GraphicsManagerFunc> registerHandler(GraphicsManagerFunc func);
  void unregisterHandler(std::shared_ptr<GraphicsManagerFunc> ptr);

  void startCameraShake(float duration, float magnitude, float speed);
  void reshape(int width, int height);
  void update();
};
} // namespace BBong

#endif // GRAPHICSMANAGER_HPP