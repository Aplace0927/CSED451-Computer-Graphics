#include "bullet.hpp"

Bullet::Bullet::Bullet():
#pragma region Constructor
    Object::Object(
        // Initial position at origin; will be updated immediately after creation
        glm::vec3(0.0f, 0.0f, 0.0f), 
        Shape::Shape<glm::vec3, Shape::RGBColor>(
            // subshapes: vector of subshapes, each subshape is a vector of vertices
            std::vector<std::vector<glm::vec3>>{
                {
                    glm::vec3(-0.01f,  0.01f, 0.0f),
                    glm::vec3( 0.01f,  0.01f, 0.0f),
                    glm::vec3( 0.01f, -0.01f, 0.0f),
                    glm::vec3(-0.01f, -0.01f, 0.0f),
                    glm::vec3(-0.01f,  0.01f, 0.0f),
                }
            },
            // colors: vector of color sets, each set is a vector of colors for the subshape
            std::vector<std::vector<Shape::RGBColor>>{
                {
                    Shape::RGBColor(1.0f, 0.7734f, 0.2227f),
                    Shape::RGBColor(1.0f, 0.7734f, 0.2227f),
                    Shape::RGBColor(1.0f, 0.7734f, 0.2227f),
                    Shape::RGBColor(1.0f, 0.7734f, 0.2227f),
                    Shape::RGBColor(1.0f, 0.7734f, 0.2227f)
                }
            },
            // drawMethod: vector of draw methods for each subshape
            std::vector<unsigned int>{ GL_TRIANGLE_FAN }
        )
    ),
    bullet_origin(glm::vec3(0.0f, 0.0f, 0.0f)),
    movement_pattern(BulletPattern::empty()),
    bullet_shooter(BulletType::NONE),
    created_time(0) { 
        Object::setStatus(false);
    }
#pragma endregion

void Bullet::Bullet::draw(time_t current_time) {
    setPosition(movement_pattern(bullet_origin, current_time - created_time));
    Object::draw();
}

void Bullet::Bullet::deactivate() {
    Object::setStatus(false);
    bullet_origin = glm::vec3(0.0f, 0.0f, 0.0f);
    movement_pattern = BulletPattern::empty();
    bullet_shooter = BulletType::NONE;
    created_time = 0;
    setReleaseFunction(nullptr);
    hitDetectFunction = nullptr;
    hitEventFunction = nullptr;
}

void Bullet::Bullet::activate(
    glm::vec3 origin,
    std::function<glm::vec3(glm::vec3, time_t)> pattern,
    BulletType shooter,
    std::function<void()> releaseFunc,
    std::function<bool(const BoundingBox::BoundingBox<glm::vec3>&)> hitDetectFunc,
    std::function<void()> hitEventFunc
) {
    bullet_origin = origin;
    movement_pattern = pattern;
    bullet_shooter = shooter;
    created_time = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();
    setReleaseFunction(releaseFunc);
    hitDetectFunction = hitDetectFunc;
    hitEventFunction = hitEventFunc;
    setPosition(movement_pattern(bullet_origin, 0));
    Object::setStatus(true);
}

bool Bullet::Bullet::isInRenderBounds(const glm::vec3& pos) {
    return pos.x > GameConfig::GAME_RENDER_LEFT_LIMIT &&
        pos.x < GameConfig::GAME_RENDER_RIGHT_LIMIT &&
        pos.y > GameConfig::GAME_RENDER_LOWER_LIMIT &&
        pos.y < GameConfig::GAME_RENDER_UPPER_LIMIT;
}

void Bullet::Bullet::update(time_t time) {
    if (!Object::getStatus())
        return;

    if (!isInRenderBounds(getCenter()))
        callReleaseFunction();

    draw(time);
}

void Bullet::Bullet::fixedUpdate() {
    if (!Object::getStatus()) {
        return;
    }
    // We solve the error cased by missing hitDetectFunction or hitEventFunction - enemypattern
    // Collision with target 
    if (hitDetectFunction(getBoundingBox())) {
        hitEventFunction();
        callReleaseFunction();
    }
}