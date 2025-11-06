#ifndef BACKGROUNDBOUNDINGBOX_HPP
#define BACKGROUNDBOUNDINGBOX_HPP

#include <memory>

#include "BBong/gameobject.hpp"
#include "BBong/renderer3d.hpp"
#include "BBong/collider3d.hpp"
#include "BBong/component.hpp"
#include "BBong/objfileloader.hpp"
#include "BBong/mesh3d.hpp"
#include "objectpool.hpp"
#include "config.hpp"
#include "bullet.hpp"
#include "gamestate.hpp"

extern BBong::GameState gameState;

namespace BBong {
class BackgroundBoundingBox : public ClonableComponent<BackgroundBoundingBox> {
public:
  explicit BackgroundBoundingBox(GameObject *owner)
      : ClonableComponent(owner) {
    auto meshRenderer = addComponent<MeshRenderer3D>();
    //meshRenderer->SetMesh(createRainbowHexagonMesh(100));

    std::vector<Vertex3D> vertices = {
        {glm::vec3(-GameConfig::WINDOW_WIDTH / 2, -GameConfig::WINDOW_HEIGHT / 2, -GameConfig::WINDOW_DEPTH / 2), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
        {glm::vec3(-GameConfig::WINDOW_WIDTH / 2, -GameConfig::WINDOW_HEIGHT / 2,  GameConfig::WINDOW_DEPTH / 2), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
        {glm::vec3(-GameConfig::WINDOW_WIDTH / 2,  GameConfig::WINDOW_HEIGHT / 2, -GameConfig::WINDOW_DEPTH / 2), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
        {glm::vec3(-GameConfig::WINDOW_WIDTH / 2,  GameConfig::WINDOW_HEIGHT / 2,  GameConfig::WINDOW_DEPTH / 2), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
        {glm::vec3( GameConfig::WINDOW_WIDTH / 2, -GameConfig::WINDOW_HEIGHT / 2, -GameConfig::WINDOW_DEPTH / 2), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
        {glm::vec3( GameConfig::WINDOW_WIDTH / 2, -GameConfig::WINDOW_HEIGHT / 2,  GameConfig::WINDOW_DEPTH / 2), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
        {glm::vec3( GameConfig::WINDOW_WIDTH / 2,  GameConfig::WINDOW_HEIGHT / 2, -GameConfig::WINDOW_DEPTH / 2), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
        {glm::vec3( GameConfig::WINDOW_WIDTH / 2,  GameConfig::WINDOW_HEIGHT / 2,  GameConfig::WINDOW_DEPTH / 2), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
    };
    std::vector<unsigned int> indices = {
        0, 2, 3, 1,
        4, 5, 7, 6,
        0, 1, 5, 4,
        2, 3, 7, 6,
        0, 2, 6, 4,
        1, 3, 7, 5,
    };
    meshRenderer->SetMesh(
        std::make_shared<Mesh3D>(vertices, indices)
    );
    meshRenderer->forceGraphicStyleMode(GraphicStyle::_GAME_BOUNDINGBOX);
    addComponent<BoxCollider3D>();
  };

  BackgroundBoundingBox(const BackgroundBoundingBox &other) : ClonableComponent(nullptr) { }

  ~BackgroundBoundingBox() override { }

  void update() override { }
  void fixedUpdate() override { }
};
} // namespace BBong
#endif // BackgroundBoundingBox_HPP