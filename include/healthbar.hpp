#ifndef HEALTHBAR_HPP
#define HEALTHBAR_HPP

#include "BBong/gameobject.hpp"

namespace BBong {
class HealthBar : public Component {
public:
  void update() override;
  void fixedUpdate() override;

  HealthBar();
  HealthBar(const glm::vec3 &digit_position, const float digit_size,
            const glm::vec3 &gauge_position, const float gauge_width,
            const float gauge_height, int maxHealth);

  void setCurrentHealth(int health);
  int getCurrentHealth() const;
  int getMaxHealth() const;

private:
  int maxHealth;
  int currentHealth;
  glm::vec3 digit_pos;
  float digit_sz;
  glm::vec3 gauge_pos;
  float gauge_w;
  float gauge_h;
};

std::vector<glm::vec3> createHealthBarShape(glm::vec3 topleft,
                                            glm::vec3 bottomright, float gauge);
//std::vector<Shape::RGBColor> createHealthBarColors(float gauge);
} // namespace HealthBar

#endif // HEALTHBAR_HPP