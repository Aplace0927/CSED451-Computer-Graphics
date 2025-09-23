#include "healthbar.hpp"

HealthBar::HealthBar::HealthBar()
: Object::Object(
    glm::vec3(0.0f, 0.0f, 0.0f),
    Shape::Shape<glm::vec3, Shape::RGBColor>(    
        // subshapes: vector of subshapes, each subshape is a vector of vertices
        std::vector<std::vector<glm::vec3>> {{}},
        // colors: vector of color sets, each set is a vector of colors for the subshape
        std::vector<std::vector<Shape::RGBColor>> {{}},
        // drawMethod: vector of draw methods for each subshape
        std::vector<unsigned int>{GL_TRIANGLE_FAN}
    )
), maxHealth(0), currentHealth(0), digit_pos(0.0f), digit_sz(0.0f), gauge_pos(0.0f), gauge_w(0.0f), gauge_h(0.0f) {}


HealthBar::HealthBar::HealthBar(
    const glm::vec3& digit_position, 
    const float digit_size,
    const glm::vec3& gauge_position,
    const float gauge_width,
    const float gauge_height,
    int maxHealth
)
: Object::Object(
    digit_position,
    Shape::Shape<glm::vec3, Shape::RGBColor>(    
        // subshapes: vector of subshapes, each subshape is a vector of vertices
        std::vector<std::vector<glm::vec3>> {{}},
        // colors: vector of color sets, each set is a vector of colors for the subshape
        std::vector<std::vector<Shape::RGBColor>> {{}},
        // drawMethod: vector of draw methods for each subshape
        std::vector<unsigned int>{}
    )
), maxHealth(maxHealth), digit_pos(digit_position), digit_sz(digit_size), gauge_pos(gauge_position), gauge_w(gauge_width), gauge_h(gauge_height) {
    setCurrentHealth(maxHealth);    
}

void HealthBar::HealthBar::setCurrentHealth(int health) {
    currentHealth = glm::clamp(health, 0, maxHealth);

    clearSubShapes();
    
    int digitCnt = 0;
    while (health > 0) {
        std::vector<glm::vec3> vertices = Digit::getDigitVertices(health % 10);
        for (auto& vertex: vertices) {
            vertex += glm::vec3(
                digit_pos.x + GameConfig::DIGIT_SPACING * (3 - digitCnt),
                digit_pos.y,
                0.0f
            );
        }
        addSubShape(
            vertices,
            Digit::getDigitColors(health % 10, createHealthBarColors((float)currentHealth / maxHealth)[0]),
            GL_LINE_STRIP
        );
        digitCnt++;
        health /= 10;
    }

    addSubShape(
        createHealthBarShape(
            gauge_pos,
            gauge_pos + glm::vec3(gauge_w, gauge_h, 0.0f),
            (float)currentHealth / maxHealth
        ),
        createHealthBarColors((float)currentHealth / maxHealth),
        GL_TRIANGLE_FAN
    );
}


int HealthBar::HealthBar::getCurrentHealth() const {
    return currentHealth;
}

int HealthBar::HealthBar::getMaxHealth() const {
    return maxHealth;
}

void HealthBar::HealthBar::update(float time) {
    draw();
}

void HealthBar::HealthBar::fixedUpdate() {
    return;
}

std::vector<glm::vec3> HealthBar::createHealthBarShape(glm::vec3 topleft, glm::vec3 bottomright, float gauge) {
    return std::vector<glm::vec3> {
        topleft,
        topleft + glm::vec3(0.0f, (bottomright.y - topleft.y), 0.0f),
        topleft + glm::vec3((bottomright.x - topleft.x) * gauge, (bottomright.y - topleft.y), 0.0f),
        topleft + glm::vec3((bottomright.x - topleft.x) * gauge, 0.0f, 0.0f),
        topleft
    };
}

std::vector<Shape::RGBColor> HealthBar::createHealthBarColors(float gauge) {
    return std::vector<Shape::RGBColor>(
        5,
        glm::mix(
            glm::make_vec3(GameConfig::GAUGE_EMPTY_COLOR),
            glm::make_vec3(GameConfig::GAUGE_FULL_COLOR),
            gauge
        )
    );
}