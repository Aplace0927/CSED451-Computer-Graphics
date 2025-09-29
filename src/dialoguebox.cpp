#include "dialoguebox.hpp"

namespace DialogueBox {
DialogueBox::DialogueBox()
    : Object::Object(glm::vec3(0.0f, 0.0f, 0.0f),
                     Shape::Shape<glm::vec3, Shape::RGBColor>(
                         std::vector<std::vector<glm::vec3>>{{}},
                         std::vector<std::vector<Shape::RGBColor>>{{}},
                         std::vector<unsigned int>{})) {
  setStatus(false);
}

void DialogueBox::update(float time __unused) {
  if (gameState == GameState::GameState::WIN) {
    setStatus(true);
    changeShape(getWinVertices());
  } else if (gameState == GameState::GameState::LOSE) {
    setStatus(true);
    changeShape(getLoseVertices());
  }

  if (getStatus()) {
    draw();
  }
  return;
}

void DialogueBox::fixedUpdate() { return; }
} // namespace DialogueBox