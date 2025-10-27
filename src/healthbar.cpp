#include "healthbar.hpp"

namespace BBong {

int HealthBar::getCurrentHealth() const { return currentHealth; }

int HealthBar::getMaxHealth() const { return maxHealth; }

void HealthBar::update() {
}

void HealthBar::fixedUpdate() { return; }

std::vector<glm::vec3> createHealthBarShape(glm::vec3 topleft,
                                                       glm::vec3 bottomright,
                                                       float gauge) {
  return std::vector<glm::vec3>{
      topleft, topleft + glm::vec3(0.0f, (bottomright.y - topleft.y), 0.0f),
      topleft + glm::vec3((bottomright.x - topleft.x) * gauge,
                          (bottomright.y - topleft.y), 0.0f),
      topleft + glm::vec3((bottomright.x - topleft.x) * gauge, 0.0f, 0.0f),
      topleft};
}
//
//std::vector<Shape::RGBColor> createHealthBarColors(float gauge) {
//  return std::vector<Shape::RGBColor>(
//      5, glm::mix(glm::make_vec3(GameConfig::GAUGE_EMPTY_COLOR),
//                  glm::make_vec3(GameConfig::GAUGE_FULL_COLOR), gauge));
//}
} // namespace BBong