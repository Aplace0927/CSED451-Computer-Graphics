#include "game.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "BBong/camera.hpp"
#include "backgroundboundingbox.hpp"
#include "BBong/light.hpp"

namespace BBong {
Game::Game() : mainScene(new Scene) {}

void Game::Init() {
  CameraInit();
  LightInit();

  ShaderManager::getInstance().init();
  TextureManager::getInstance().init();

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
}

void Game::LightInit() {
  auto directionalLightObj = mainScene->createGameObject();
  auto dirLightComp = directionalLightObj->addComponent<Light>();
  dirLightComp->setDirectional(
      glm::vec3(0.8f, 0.8f, 0.8f),
      glm::vec3(2.0f, 2.0f, 2.0f),
      glm::vec3(1.0f, 1.0f, 1.0f) 
  );
  glm::vec3 lightDir = glm::normalize(glm::vec3(0.001f, -1.0f, 0.0f));
  glm::quat dirRot = glm::quatLookAt(lightDir, glm::vec3(0, 1, 0));
  directionalLightObj->transform->setRotation(dirRot);
}

void Game::CameraInit() {
  float halfWidth = static_cast<float>(GameConfig::WINDOW_WIDTH) / 2.0f;
  float halfHeight = static_cast<float>(GameConfig::WINDOW_HEIGHT) / 2.0f;
  float halfDepth = static_cast<float>(GameConfig::WINDOW_DEPTH) / 2.0f;
  float aspectRatio =
      static_cast<float>(GameConfig::WINDOW_WIDTH) / GameConfig::WINDOW_HEIGHT;

  cameraController =
      mainScene->createGameObject()->addComponent<CameraController>();

  // --- 1. Orthographic Camera (cam1) ---
  GameObject *cameraObj1 = mainScene->createGameObject();
  auto cam1 = cameraObj1->addComponent<Camera>();
  cam1->setProjectionType(ProjectionType::ORTHOGRAPHIC);
  cam1->setOrthographic(GameConfig::WINDOW_WIDTH, GameConfig::WINDOW_HEIGHT,
                        halfDepth, -halfDepth);
  cam1->transform->setWorldPosition(glm::vec3(0.0f));
  cam1->transform->setRotation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f));

  // --- 2. Perspective Camera (cam2) ---
  GameObject *cameraObj2 = mainScene->createGameObject();
  auto cam2 = cameraObj2->addComponent<Camera>();
  cam2->setProjectionType(ProjectionType::PERSPECTIVE);
  cam2->setPerspective(glm::radians(90.0f), aspectRatio, 0.1f,
                       10.0f * halfHeight);
  cam2->transform->setWorldPosition(glm::vec3(0.0f, 0.0f, 1.3f * halfHeight));
  cam2->transform->setRotation(glm::quat(0.0f, 0.0f, 0.0f, 0.0f));

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

  Game::getInstance().cameraController->setCamera(ProjectionMode::ORTHOGRAPHIC,
                                                  cam1);
  Game::getInstance().cameraController->setCamera(ProjectionMode::PERSPECTIVE,
                                                  cam2);
  Game::getInstance().cameraController->setCamera(ProjectionMode::TPV_TOPVIEW,
                                                  cam3);
}
} // namespace BBong