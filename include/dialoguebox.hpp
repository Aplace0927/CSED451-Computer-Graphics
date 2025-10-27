#ifndef DIALOGUEBOX_HPP
#define DIALOGUEBOX_HPP

#include <vector>

#include "BBong/component.hpp"
#include "gamestate.hpp"
#include "utility.hpp"

extern GameState::GameState gameState;

namespace BBong {
class DialogueBox : public Component {
public:
  explicit DialogueBox(GameObject *owner) : Component(owner) {};
  void update() {}
  override;
  void fixedUpdate() {}
  override;
};
}; // namespace Component

#endif // DIALOUGEBOX_HPP