#include "dialoguebox.hpp"

namespace DialogueBox {
DialogueBox::DialogueBox()
    : Object::Object(
      new Transform::Transform<glm::vec3, Shape::RGBColor>(getWinVertices())) {
  setStatus(false);
}

void DialogueBox::update(float time) {
  if (gameState.currentState == GameState::GameState::WIN) {
    setStatus(true);
    getTransform()->changeShape(getWinVertices());
  } else if (gameState.currentState == GameState::GameState::LOSE) {
    setStatus(true);
    getTransform()->changeShape(getLoseVertices());
  }

  if (getStatus()) {
    draw(Utility::getCurrentTimeMS());
  }
  return;
}

void DialogueBox::fixedUpdate() { return; }
} // namespace DialogueBox