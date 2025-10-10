#include "healthbar.hpp"

namespace HealthBar {
  HealthBar::HealthBar(
    const glm::vec3 &digit_position,
    const float digit_size,
    const glm::vec3 &gauge_position,
    const float gauge_width,
    const float gauge_height, int maxHealth
  ) : Shape::Shape<glm::vec3, glm::vec3>(
      std::vector<std::vector<glm::vec3>>{{}},
      std::vector<std::vector<glm::vec3>>{{}},
      std::vector<unsigned int>{}
    ), maxHealth(maxHealth), digit_pos(digit_position), digit_sz(digit_size),
      gauge_pos(gauge_position), gauge_w(gauge_width), gauge_h(gauge_height) {
    setCurrentHealth(maxHealth);
  }

  void HealthBar::setCurrentHealth(int health) {
    currentHealth = glm::clamp(health, 0, maxHealth);

    clearSubShapes();

    int digitCnt = 0;
    while (health > 0) {
      std::vector<glm::vec3> vertices = Digit::getDigitVertices(health % 10);
      for (auto &vertex : vertices) {
        vertex +=
            glm::vec3(digit_pos.x + GameConfig::DIGIT_SPACING * (3 - digitCnt),
                      digit_pos.y, 0.0f);
      }
      addSubShape(vertices,
                  Digit::getDigitColors(
                      health % 10,
                      createHealthBarColors((float)currentHealth / maxHealth)[0]),
                  GL_LINE_STRIP);
      digitCnt++;
      health /= 10;
    }

    addSubShape(createHealthBarShape(
                    gauge_pos, gauge_pos + glm::vec3(gauge_w, gauge_h, 0.0f),
                    (float)currentHealth / maxHealth),
                createHealthBarColors((float)currentHealth / maxHealth),
                GL_TRIANGLE_FAN);
  }

  int HealthBar::getCurrentHealth() const { return currentHealth; }

  int HealthBar::getMaxHealth() const { return maxHealth; }

  HealthBar generateHealthBar(
    const glm::vec3 &digit_position,
    const float digit_size,
    const glm::vec3 &gauge_position,
    const float gauge_width,
    const float gauge_height,
    int currentHealth,
    int maxHealth
  ) {
    HealthBar hb(
      digit_position,
      digit_size,
      gauge_position,
      gauge_width,
      gauge_height,
      maxHealth
    );
    hb.setCurrentHealth(currentHealth);
    return hb;
  }

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

  std::vector<Shape::RGBColor> createHealthBarColors(float gauge) {
    return std::vector<glm::vec3>(
        5, glm::mix(glm::make_vec3(GameConfig::GAUGE_EMPTY_COLOR),
                    glm::make_vec3(GameConfig::GAUGE_FULL_COLOR), gauge));
  }
}
