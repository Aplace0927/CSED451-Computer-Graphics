#include "game.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "BBong/camera.hpp"
#include "backgroundboundingbox.hpp"
#include "camerachanger.hpp"

namespace BBong {
Game::Game() : mainScene(new Scene) {}

void Game::Init() {
  BBong::ShaderManager::getInstance().init();

  GameObject *backgroundboundingboxObj = mainScene->createGameObject();
  backgroundboundingboxObj->addComponent<BackgroundBoundingBox>();

  playerObj = mainScene->createGameObject();
  playerObj->addComponent<Player>();

  auto enemyObj1 = mainScene->createGameObject();
  enemyObj1->addComponent<Enemy>();
  enemyObj1->transform->setWorldPosition(glm::vec3(
      GameConfig::POSITION_LEFT_LIMIT, GameConfig::POSITION_UPPER_LIMIT, 0.0f));

  auto enemyObj2 = mainScene->createGameObject();
  enemyObj2->addComponent<Enemy>();
  enemyObj2->transform->setWorldPosition(
      glm::vec3(GameConfig::POSITION_RIGHT_LIMIT,
                GameConfig::POSITION_UPPER_LIMIT, 0.0f));

  CameraInit();
}

void Game::CameraInit() {
  float halfWidth = static_cast<float>(GameConfig::WINDOW_WIDTH) / 2.0f;
  float halfHeight = static_cast<float>(GameConfig::WINDOW_HEIGHT) / 2.0f;
  float halfDepth = static_cast<float>(GameConfig::WINDOW_DEPTH) / 2.0f;
  float aspectRatio =
      static_cast<float>(GameConfig::WINDOW_WIDTH) / GameConfig::WINDOW_HEIGHT;

  CameraChanger *cameraController =
      mainScene->createGameObject()->addComponent<CameraChanger>();

  // --- 1. Orthographic Camera (cam1) ---
  GameObject *cameraObj1 = mainScene->createGameObject();
  auto cam1 = cameraObj1->addComponent<Camera>();
  cam1->setProjectionType(ProjectionType::ORTHOGRAPHIC);
  cam1->setOrthographic(GameConfig::WINDOW_WIDTH, GameConfig::WINDOW_HEIGHT,
                        halfDepth, -halfDepth);
  cam1->transform->setWorldPosition(glm::vec3(0.0f));
  cam1->transform->setRotation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f));
  cameraController->Ortho_Camera = cam1;

  // --- 2. Perspective Camera (cam2) ---
  GameObject *cameraObj2 = mainScene->createGameObject();
  auto cam2 = cameraObj2->addComponent<Camera>();
  cam2->setProjectionType(ProjectionType::PERSPECTIVE);
  cam2->setPerspective(glm::radians(90.0f), aspectRatio, 0.1f,
                       10.0f * halfHeight);
  cam2->transform->setWorldPosition(glm::vec3(0.0f, 0.0f, 1.3f * halfHeight));
  cam2->transform->setRotation(glm::quat(0.0f, 0.0f, 0.0f, 0.0f));
  cameraController->Perspective_Camera = cam2;

  // --- 3. TPV/TopView Camera (cam3) ---
  GameObject *cameraObj3 = mainScene->createGameObject();
  auto cam3 = cameraObj3->addComponent<Camera>();
  cam3->setProjectionType(ProjectionType::PERSPECTIVE);
  cam3->setPerspective(glm::radians(90.0f), aspectRatio, 0.1f,
                       3.0f * halfHeight);

  glm::vec3 eye = glm::vec3(0.0f, -1.2f * halfHeight, 70.0f);
  glm::vec3 center = glm::vec3(0.0f, 1.0f * halfHeight, -50.0f);
  glm::vec3 up = glm::vec3(0.0f, 0.0f, 1.0f);

  glm::mat4 viewMatrix = glm::lookAt(eye, center, up);
  glm::mat4 worldMatrix = glm::inverse(viewMatrix);

  cam3->transform->setWorldPosition(glm::vec3(worldMatrix[3]));
  cam3->transform->setRotation(glm::quat_cast(worldMatrix));

  cameraController->TPV_Camera = cam3;

  // --- 4. Player Camera (cam4) ---
  GameObject *cameraObj4 = mainScene->createGameObject();
  cameraObj4->transform->setParent(playerObj->transform);
  auto cam4 = cameraObj4->addComponent<Camera>();
  cam4->setProjectionType(ProjectionType::PERSPECTIVE);
  cam4->setPerspective(glm::radians(60.0f), aspectRatio, 0.1f,
                       10.0f * halfHeight);

  cam4->transform->setLocalPosition(
      glm::vec3(0.0f, halfDepth, -0.1 * halfHeight));
  cam4->transform->setRotation(
      glm::quat(glm::radians(glm::vec3(-50.0f, 180.0f, 0.0f))));
  cameraController->Player_Camera = cam4;

  GraphicsManager::getInstance().setMainCamera(cam2);
}
} // namespace BBong