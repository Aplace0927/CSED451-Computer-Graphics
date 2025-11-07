#include "BBong/graphicsmanager.hpp"

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <chrono>
#include <algorithm>
#include <iostream>

#include "config.hpp"
#include "utility.hpp"
#include "BBong/input.hpp"

namespace BBong {
std::shared_ptr<GraphicsManagerFunc>
GraphicsManager::registerHandler(GraphicsManagerFunc func) {
  std::lock_guard<std::recursive_mutex> lock(updateHandlerMutex);
  auto ptr = std::make_shared<GraphicsManagerFunc>(func);
  handlers.push_back(ptr);
  return ptr;
}

void GraphicsManager::unregisterHandler(
    std::shared_ptr<GraphicsManagerFunc> ptr) {
  std::lock_guard<std::recursive_mutex> lock(updateHandlerMutex);
  handlers.erase(std::remove(handlers.begin(), handlers.end(), ptr),
                 handlers.end());
}

void GraphicsManager::update() {
  // --- 1. Projection 매트릭스 설정 ---
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  float halfWidth = static_cast<float>(GameConfig::WINDOW_WIDTH) / 2;
  float halfHeight = static_cast<float>(GameConfig::WINDOW_HEIGHT) / 2;
  float halfDepth = static_cast<float>(GameConfig::WINDOW_DEPTH) / 2;

  switch (Input::getInstance().projectionMode) {
  case Input::PERSPECTIVE:
    gluPerspective(75.0f, static_cast<float>(halfWidth) / halfHeight, 0.1f,
                   3 * halfHeight);
    glTranslatef(0.0f, 0.0f, -1.5f * halfHeight);
    break;
  case Input::ORTHOGRAPHIC:
    glOrtho(-halfWidth, halfWidth, -halfHeight, halfHeight, halfDepth,
            -halfDepth);
    break;
  case Input::TPV_TOPVIEW:
    gluPerspective(75.0f, 1.5f * static_cast<float>(halfWidth) / halfHeight,
                   0.1f, 3 * halfHeight);
    gluLookAt(0.0f, -1.5f * halfHeight, 100.0f, 0.0f, halfHeight, -100.0f, 0.0f,
              0.0f, 1.0f);
    break;
  }

  // --- 2. ModelView 매트릭스 초기화 ---
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // --- 타이머 및 핸들러 복사 ---
  auto now = std::chrono::high_resolution_clock::now();
  Utility::DeltaTime = std::chrono::duration<float>(now - lastFrame).count();
  lastFrame = now;

  std::vector<std::shared_ptr<GraphicsManagerFunc>> updateHandlerCopy;
  {
    std::lock_guard<std::recursive_mutex> lock(updateHandlerMutex);
    updateHandlerCopy = handlers; // Create a copy to avoid holding the lock
  }

  // --- 3. 카메라 셰이크 적용 (그리기 전) ---
  if (shaking) {
    std::cout << "Shaking: " << shakeTimer << " / " << shakeDuration << "\n";
    shakeTimer += Utility::DeltaTime;
    if (shakeTimer >= shakeDuration) {
      shaking = false;
    } else {
      applyCameraShake();
    }
  }

  // --- 4. 화면 지우기 ---

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // --- 5. 모든 객체 렌더링 ---
  // `return`을 제거하여, 핸들러가 없어도 화면이 clear되고 swap되도록
  // 수정
  if (!updateHandlerCopy.empty()) {
    for (auto &handler : updateHandlerCopy) {
      if (handler == nullptr) {
        continue;
      }
      (*handler)(); // 셰이크가 적용된 ModelView 매트릭스 위에서 렌더링
    }
  }

  // --- 6. 버퍼 스왑 및 재그리기 요청 ---
  glutSwapBuffers();
  glutPostRedisplay();
}

void GraphicsManager::applyCameraShake() const {
  float offsetX = glm::sin(shakeTimer * shakeSpeed) * shakeMagnitude;
  float offsetY = glm::cos(shakeTimer * shakeSpeed * 1.3f) * shakeMagnitude;

  glTranslatef(-offsetX, -offsetY, 0.0f);
}

void GraphicsManager::startCameraShake(float duration, float magnitude,
                                       float speed) {
  shakeDuration = duration;
  shakeMagnitude = magnitude;
  shakeSpeed = speed;
  shakeTimer = 0.0f;
  shaking = true;
}

void GraphicsManager::reshape(int width, int height) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  float halfWidth = static_cast<float>(GameConfig::WINDOW_WIDTH) / 2;
  float halfHeight = static_cast<float>(GameConfig::WINDOW_HEIGHT) / 2;

  switch (Input::getInstance().projectionMode) {
  case Input::PERSPECTIVE:
    gluPerspective(75.0f, static_cast<float>(halfWidth) / halfHeight, 0.1f,
                   3 * halfHeight);
    glTranslatef(0.0f, 0.0f, -1.5f * halfHeight);
    break;
  case Input::ORTHOGRAPHIC:
    glOrtho(-halfWidth, halfWidth, -halfHeight, halfHeight, -1.0f, 1.0f);
    break;
  case Input::TPV_TOPVIEW:
    gluPerspective(75.0f, 1.5f * static_cast<float>(halfWidth) / halfHeight,
                   0.1f, 3 * halfHeight);
    gluLookAt(0.0f, -1.5f * halfHeight, 100.0f, 0.0f, halfHeight, -100.0f, 0.0f,
              0.0f, 1.0f);
    break;
  }

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  float originalAspect =
      static_cast<float>(GameConfig::WINDOW_WIDTH) / GameConfig::WINDOW_HEIGHT;
  float aspect = static_cast<float>(width) / height;

  if (aspect > originalAspect) {
    int newWidth = originalAspect * height;
    int xOffset = (width - newWidth) / 2;
    glViewport(xOffset, 0, newWidth, height);
  } else {
    int newHeight = width / originalAspect;
    int yOffset = (height - newHeight) / 2;
    glViewport(0, yOffset, width, newHeight);
  }
}
} // namespace BBong