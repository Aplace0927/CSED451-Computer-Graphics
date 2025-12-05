#include "BBong/graphicsmanager.hpp"
#include "BBong/camera.hpp" // Camera Ŭ���� ��ü ���� �ʿ�

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <chrono>

#include "config.hpp"
#include "utility.hpp"
#include "BBong/shadermanager.hpp"
#include "BBong/light.hpp"

namespace BBong {
#pragma region register
std::shared_ptr<GraphicsManagerFunc>
GraphicsManager::registerUpdateHandler(GraphicsManagerFunc func) {
  std::lock_guard<std::recursive_mutex> lock(updateHandlerMutex);
  auto ptr = std::make_shared<GraphicsManagerFunc>(func);
  this->updatehandler = ptr;
  return ptr;
}

void GraphicsManager::unregisterUpdateHandler(
    std::shared_ptr<GraphicsManagerFunc> ptr) {
  std::lock_guard<std::recursive_mutex> lock(updateHandlerMutex);
  if (this->updatehandler == ptr) {
    this->updatehandler = nullptr;
  }
}

std::shared_ptr<GraphicsManagerFunc>
GraphicsManager::registerLateUpdateHandler(GraphicsManagerFunc func) {
  std::lock_guard<std::recursive_mutex> lock(updateHandlerMutex);
  auto ptr = std::make_shared<GraphicsManagerFunc>(func);
  this->lateUpdatehandler = ptr;
  return ptr;
}

void GraphicsManager::unregisterLateUpdateHandler(
    std::shared_ptr<GraphicsManagerFunc> ptr) {
  std::lock_guard<std::recursive_mutex> lock(updateHandlerMutex);
  if (this->lateUpdatehandler == ptr) {
    this->lateUpdatehandler = nullptr;
  }
}

std::shared_ptr<GraphicsManagerFunc>
GraphicsManager::registerRenderUpdateHandler(GraphicsManagerFunc func) {
  std::lock_guard<std::recursive_mutex> lock(updateHandlerMutex);
  auto ptr = std::make_shared<GraphicsManagerFunc>(func);
  this->renderUpdatehandler = ptr;
  return ptr;
}

void GraphicsManager::unregisterRenderUpdateHandler(
    std::shared_ptr<GraphicsManagerFunc> ptr) {
  std::lock_guard<std::recursive_mutex> lock(updateHandlerMutex);
  if (this->renderUpdatehandler == ptr) {
    this->renderUpdatehandler = nullptr;
  }
}
#pragma endregion

void GraphicsManager::setMainCamera(Camera *camera) { m_mainCamera = camera; }

void GraphicsManager::update() {
  // --- 1. Time Calculation ---
  auto now = std::chrono::high_resolution_clock::now();
  Utility::DeltaTime = std::chrono::duration<float>(now - lastFrame).count();
  lastFrame = now;

  // --- 2. Thread Safety: Get Local Shared Pointers ---
  std::shared_ptr<GraphicsManagerFunc> currentUpdate;
  std::shared_ptr<GraphicsManagerFunc> currentLateUpdate;
  std::shared_ptr<GraphicsManagerFunc> currentRenderUpdate;

  {
    std::lock_guard<std::recursive_mutex> lock(updateHandlerMutex);
    currentUpdate = updatehandler;
    currentLateUpdate = lateUpdatehandler;
    currentRenderUpdate = renderUpdatehandler;
  }

  // --- 3. Update (Game Logic) ---
  if (currentUpdate) {
    (*currentUpdate)();
  }

  // --- 4. Render Preparation ---
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (m_mainCamera) {
    glm::mat4 view = m_mainCamera->getViewMatrix();
    glm::mat4 projection = m_mainCamera->getProjectionMatrix();

    ShaderManager::getInstance().attachProgram("basic_shader");
    ShaderManager::getInstance().setUniformValue("basic_shader", "uMat4View", view);
    ShaderManager::getInstance().setUniformValue("basic_shader", "uMat4Projection", projection);
  }

  // --- 5. Late Update (Camera logic, lights) ---
  Light::ResetFrame();
  if (currentLateUpdate) {
    (*currentLateUpdate)();
  }

  // --- 6. Rendering (Draw Calls) ---
  if (currentRenderUpdate) {
    (*currentRenderUpdate)();
  }

  // --- 7. Buffer Swap ---
  glutSwapBuffers();
  glutPostRedisplay();
}

void GraphicsManager::reshape(int width, int height) {
  float originalAspect =
      static_cast<float>(GameConfig::WINDOW_WIDTH) / GameConfig::WINDOW_HEIGHT;

  float currentAspect = static_cast<float>(width) / height;

  int xOffset = 0;
  int yOffset = 0;
  int newWidth = width;
  int newHeight = height;

  if (currentAspect > originalAspect) {
    newWidth = static_cast<int>(height * originalAspect);
    xOffset = (width - newWidth) / 2;
  } else {
    newHeight = static_cast<int>(width / originalAspect);
    yOffset = (height - newHeight) / 2;
  }

  glViewport(xOffset, yOffset, newWidth, newHeight);

  if (m_mainCamera) {
    m_mainCamera->updateAspectRatio(originalAspect);
  }
}
} // namespace BBong