#ifndef DIALOGUEBOX_HPP
#define DIALOGUEBOX_HPP

#include <vector>

#include "object.hpp"
#include "gamestate.hpp"
#include "digit.hpp"
#include "utility.hpp"

extern GameState::GameState gameState;

namespace DialogueBox {
class DialogueBox : public Object::Object<glm::vec3, Shape::RGBColor> {
public:
  DialogueBox();
  void update(float time) override;
  void fixedUpdate() override;
};
} // namespace DialogueBox

#endif // DIALOUGEBOX_HPP