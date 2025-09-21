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
) {}


HealthBar::HealthBar::HealthBar(
    const glm::vec3& position, 
    int maxHealth
)
: Object::Object(
    position,
    Shape::Shape<glm::vec3, Shape::RGBColor>(    
        // subshapes: vector of subshapes, each subshape is a vector of vertices
        std::vector<std::vector<glm::vec3>> {{}},
        // colors: vector of color sets, each set is a vector of colors for the subshape
        std::vector<std::vector<Shape::RGBColor>> {{}},
        // drawMethod: vector of draw methods for each subshape
        std::vector<unsigned int>{}
    )
), maxHealth(maxHealth) {
    setCurrentHealth(maxHealth);    
}

void HealthBar::HealthBar::setCurrentHealth(int health) {
    currentHealth = glm::clamp(health, 0, maxHealth);

    clearSubShapes();
    
    int digitCnt = 0;
    while (health > 0) {
        std::vector<glm::vec3> vertices = Digit::getDigitVertices(health % 10);
        for (auto& vertex: vertices) {
            vertex += glm::vec3(GameConfig::ENEMY_GAUGE_X + GameConfig::FONT_DIGIT_SIZE * 6 * (3 - digitCnt), GameConfig::ENEMY_GAUGE_Y - 0.1f, 0.0f); // Slightly offset in z to avoid z-fighting
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
        createHealthBarShape((float)currentHealth / maxHealth),
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

void HealthBar::HealthBar::update(time_t time) {
    draw();
}

void HealthBar::HealthBar::fixedUpdate() {
    return;
}

std::vector<glm::vec3> HealthBar::createHealthBarShape(float gauge) {
    return std::vector<glm::vec3> {
        glm::vec3(GameConfig::ENEMY_GAUGE_X, GameConfig::ENEMY_GAUGE_Y, 0.0f),
        glm::vec3(GameConfig::ENEMY_GAUGE_X + GameConfig::ENEMY_GAUGE_WIDTH, GameConfig::ENEMY_GAUGE_Y, 0.0f),
        glm::vec3(GameConfig::ENEMY_GAUGE_X + GameConfig::ENEMY_GAUGE_WIDTH, GameConfig::ENEMY_GAUGE_Y + glm::mix(0.0f, GameConfig::ENEMY_GAUGE_HEIGHT, gauge), 0.0f),
        glm::vec3(GameConfig::ENEMY_GAUGE_X, GameConfig::ENEMY_GAUGE_Y + glm::mix(0.0f, GameConfig::ENEMY_GAUGE_HEIGHT, gauge), 0.0f),
        glm::vec3(GameConfig::ENEMY_GAUGE_X, GameConfig::ENEMY_GAUGE_Y, 0.0f)
    };
}

std::vector<Shape::RGBColor> HealthBar::createHealthBarColors(float gauge) {
    return std::vector<Shape::RGBColor>(
        5,
        glm::mix(
            glm::make_vec3(GameConfig::ENEMY_GAUGE_EMPTY_COLOR),
            glm::make_vec3(GameConfig::ENEMY_GAUGE_FULL_COLOR),
            gauge
        )
    );
}