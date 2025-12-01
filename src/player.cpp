#include "player.hpp"

#include "cameracontroller.hpp"

namespace BBong {
Player::Player(GameObject *owner)
    : ClonableComponent(owner), meshRenderer(nullptr) {
  // 1. Player Bullet Object
  GameObject *bulletPrefab = createBulletPrefab();
  bullets = std::make_shared<ObjectPool>(*bulletPrefab, nullptr, 0);
  bulletPrefab->getComponent<Bullet>()->SetBulletPool(bullets);

  // 2. Player Mesh Component
  GameObject *renderObj =
      Game::getInstance().mainScene->createGameObject(transform);
  meshRenderer = renderObj->addComponent<MeshRenderer3D>();

#ifdef ASSETS_DIRECTORY
  meshRenderer->setMesh(ObjLoader::load(ASSETS_DIRECTORY "obj/jet.obj"));
  meshRenderer->setTextureID(TextureManager::getInstance().getTexture(
      ASSETS_DIRECTORY "texture/diffuse/diffuse_jet.png"));
#else
  printf("Warning: ASSETS_DIRECTORY not defined.\n");
  meshRenderer->setMesh(ObjLoader::load("assets/obj/jet.obj"));
  meshRenderer->setTextureID(TextureManager::getInstance().getTexture(
      "assets/texture/diffuse/diffuse_jet.png"));
#endif
  meshRenderer->setDefaultColor(glm::vec3(0.0f, 1.0f, 1.0f));

  transform->setWorldPosition(
      glm::vec3(0.0f, -GameConfig::WINDOW_HEIGHT / 4.0f, 0.0f));
  transform->setScale(glm::vec3(5.0f));

  transform->setRotation(glm::quat(glm::vec3(0.0f)));
  shootingPoint = Game::getInstance().mainScene->createGameObject(transform);
  shootingPoint->transform->setLocalPosition(glm::vec3(0, 0, 7));

  // 3. Player Health Gem Origin
  healthGemOrigin = Game::getInstance().mainScene->createGameObject(transform);

  for (int i = 0; i < playerHealth; ++i) {
    GameObject *healthGem =
        Game::getInstance().mainScene->createGameObject(transform);
    healthGem->transform->setLocalPosition(glm::vec3(
        10 * glm::cos(glm::radians(360.0f * i / playerHealth)),
        10 * glm::sin(glm::radians(360.0f * i / playerHealth)), 0.0f));
    auto healthGemMesh = healthGem->addComponent<MeshRenderer3D>();
#ifdef ASSETS_DIRECTORY
    healthGemMesh->setMesh(
        ObjLoader::load(ASSETS_DIRECTORY "obj/star_sharp.obj"));
    healthGemMesh->setTextureID(TextureManager::getInstance().getTexture(
        ASSETS_DIRECTORY "texture/diffuse/diffuse_star.png"));
#else
    printf("Warning: ASSETS_DIRECTORY not defined.\n");
    healthGemMesh->setMesh(ObjLoader::load("assets/obj/star_sharp.obj"));
    healthGemMesh->setTextureID(TextureManager::getInstance().getTexture(
        "assets/texture/diffuse/diffuse_star.png"));
#endif
    healthGemMesh->setDefaultColor(glm::vec3(1.0f, 1.0f, 0.5f));
    healthGem->transform->setParent(healthGemOrigin->transform);
    healthGems.push_back(healthGem);

    // Player Collider
    auto collider = addComponent<BoxCollider3D>();
    collider->setLayer(GameConfig::CollisionLayer::PLAYER);
    std::vector<glm::vec3> vertices = {glm::vec3(-3.0f, -3.0f, -3.0f),
                                       glm::vec3(3.0f, 3.0f, 3.0f)};
    collider->SetBoundingBox(vertices);
  }

  // --- 4. Player Camera ---
  float halfWidth = static_cast<float>(GameConfig::WINDOW_WIDTH) / 2.0f;
  float halfHeight = static_cast<float>(GameConfig::WINDOW_HEIGHT) / 2.0f;
  float halfDepth = static_cast<float>(GameConfig::WINDOW_DEPTH) / 2.0f;
  float aspectRatio =
      static_cast<float>(GameConfig::WINDOW_WIDTH) / GameConfig::WINDOW_HEIGHT;

  GameObject *cameraObj4 =
      Game::getInstance().mainScene->createGameObject(transform);
  Camera *cam4 = cameraObj4->addComponent<Camera>();
  cam4->setProjectionType(ProjectionType::PERSPECTIVE);
  cam4->setPerspective(glm::radians(60.0f), aspectRatio, 0.1f,
                       10.0f * halfHeight);

  glm::vec3 initialPos = glm::vec3(0.0f, halfDepth, -0.1 * halfHeight);
  cam4->transform->setLocalPosition(initialPos);
  cam4->transform->setRotation(
      glm::quat(glm::radians(glm::vec3(-50.0f, 180.0f, 0.0f))));

  Game::getInstance().cameraController->setCamera(ProjectionMode::PLAYER_VIEW,
                                                  cam4);
}

Player::Player(const Player &other)
    : ClonableComponent(nullptr), meshRenderer(nullptr) {
  this->bullets = other.bullets;
  this->direction = other.direction;
  this->shootingPoint = other.shootingPoint;
  this->healthGemOrigin = other.healthGemOrigin;
  this->healthGems = other.healthGems;
}

Player::~Player() { bullets.reset(); }

void Player::update() {
  direction = Input::getInstance().playerMoveVec;
  isShooting = Input::getInstance().isShooting;

  shootingCooldown += Utility::DeltaTime;
  reviveCooldown += Utility::DeltaTime;

  if (playerHealth <= 0) {
    this->setActive(false);
    return;
  }

  if (reviveCooldown >= GameConfig::REVIVE_COOLDOWN_TIME_SEC) {
    isLive = true;
    meshRenderer->gameObject->setActive(true);
  }

  animateViewDirection = glm::mix(animateViewDirection, direction, GameConfig::ANIMATION_BLEND_SPEED);
  transform->setRotation(glm::quat(glm::radians(glm::vec3(
      -90.0f + 20.0f * animateViewDirection.y, 180.0f + 10.0f * animateViewDirection.x, 0.0f))));

  healthGemOrigin->transform->rotate(90.0f * Utility::DeltaTime,
                                     glm::normalize(glm::vec3(0, 1, 1)));

  if (isShooting &&
      shootingCooldown >= GameConfig::SHOOTING_COOLDOWN_TIME_SEC) {
    auto newBullet = bullets->acquire();
#ifdef ASSETS_DIRECTORY
    newBullet->getComponent<MeshRenderer3D>()->setTextureID(
        TextureManager::getInstance().getTexture(
            ASSETS_DIRECTORY "texture/diffuse/diffuse_rice.png"));
#else
    newBullet->getComponent<MeshRenderer3D>()->setTextureID(
        TextureManager::getInstance().getTexture(
            "assets/texture/diffuse/diffuse_rice.png"));
#endif
    newBullet->transform->setWorldPosition(
        shootingPoint->transform->getWorldPosition());
    shootingCooldown = 0;
  }
}

void Player::fixedUpdate() {
  transform->translate(direction * Utility::FixedDeltaTime * speed);

  glm::vec3 currentpos = transform->getWorldPosition();

  transform->setWorldPosition(
      glm::vec3(glm::clamp(currentpos.x, GameConfig::POSITION_LEFT_LIMIT,
                           GameConfig::POSITION_RIGHT_LIMIT),
                glm::clamp(currentpos.y, GameConfig::POSITION_LOWER_LIMIT,
                           GameConfig::POSITION_UPPER_LIMIT),
                currentpos.z));
}

void Player::collision3D(Collider3D *collider) {
  if (playerHealth > 0 && isLive) {
    Game::getInstance().cameraController->startCameraShake(0.15f, 3000.0f,
                                                           60.0f);
    --playerHealth;
    isLive = false;
    reviveCooldown = 0.0f;
    meshRenderer->gameObject->setActive(false);
    if (!healthGems.empty()) {
      GameObject *lostHealthGem = healthGems.back();
      healthGems.pop_back();
      lostHealthGem->setActive(false);
    }
  }
}

GameObject *Player::createBulletPrefab() {
  auto bulletPrefab = Game::getInstance().mainScene->createGameObject();
  bulletPrefab->setActive(false);
  bulletPrefab->addComponent<PlayerBullet>();
  return bulletPrefab;
}
} // namespace BBong