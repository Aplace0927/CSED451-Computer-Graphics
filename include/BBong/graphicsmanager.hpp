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
class Camera;
typedef std::function<void()> GraphicsManagerFunc;

class GraphicsManager : public Singleton<GraphicsManager> {
private:
  std::chrono::high_resolution_clock::time_point lastFrame;
  GraphicsManager(const GraphicsManager &) = delete;
  GraphicsManager &operator=(const GraphicsManager &) = delete;

  std::shared_ptr<GraphicsManagerFunc> updatehandler;
  std::shared_ptr<GraphicsManagerFunc> lateUpdatehandler;
  std::shared_ptr<GraphicsManagerFunc> renderUpdatehandler;

  std::recursive_mutex updateHandlerMutex;

  Camera *m_mainCamera = nullptr;

public:
  GraphicsManager() { lastFrame = std::chrono::high_resolution_clock::now(); };
  ~GraphicsManager() = default;

  std::shared_ptr<GraphicsManagerFunc>
  registerUpdateHandler(GraphicsManagerFunc func);
  void unregisterUpdateHandler(std::shared_ptr<GraphicsManagerFunc> ptr);

  std::shared_ptr<GraphicsManagerFunc>
  registerLateUpdateHandler(GraphicsManagerFunc func);
  void unregisterLateUpdateHandler(std::shared_ptr<GraphicsManagerFunc> ptr);

  std::shared_ptr<GraphicsManagerFunc>
  registerRenderUpdateHandler(GraphicsManagerFunc func);
  void unregisterRenderUpdateHandler(std::shared_ptr<GraphicsManagerFunc> ptr);

  void reshape(int width, int height);
  void update();

  void setMainCamera(Camera *camera);
  Camera *getMainCamera() const { return m_mainCamera; }
};
} // namespace BBong

#endif // GRAPHICSMANAGER_HPP