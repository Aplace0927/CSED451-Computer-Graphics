#include "dialoguebox.hpp"

namespace DialogueBox {
DialogueBox::DialogueBox()
    : Object::Object(
      new SceneGraph::SceneGraph<glm::vec3, Shape::RGBColor>(getWinVertices())) {
  setStatus(false);
}

void DialogueBox::update(float time __unused) {
  if (gameState == GameState::GameState::WIN) {
    setStatus(true);
    getSceneGraph()->changeShape(getWinVertices());
  } else if (gameState == GameState::GameState::LOSE) {
    setStatus(true);
    getSceneGraph()->changeShape(getLoseVertices());
  }

  if (getStatus()) {
    draw(Utility::getCurrentTimeMS());
  }
  return;
}

void DialogueBox::fixedUpdate() { return; }
} // namespace DialogueBox