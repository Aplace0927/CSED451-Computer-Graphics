#include "bullet.hpp"

Bullet::Bullet::Bullet(): 
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
    active(false),
    bullet_origin(glm::vec3(0.0f, 0.0f, 0.0f)),
    movement_pattern(BulletPattern::empty()),
    bullet_shooter(BulletType::NONE),
    created_time(0) { }

void Bullet::Bullet::draw(time_t current_time) {
    setPosition(movement_pattern(bullet_origin, current_time - created_time));
    Object::draw();
}

void Bullet::Bullet::deactivate() {
    active = false;
    bullet_origin = glm::vec3(0.0f, 0.0f, 0.0f);
    movement_pattern = BulletPattern::empty();
    bullet_shooter = BulletType::NONE;
    created_time = 0;
}

void Bullet::Bullet::activate(
    glm::vec3 origin,
    std::function<glm::vec3(glm::vec3, time_t)> pattern,
    BulletType shooter
) {
    bullet_origin = origin;
    movement_pattern = pattern;
    bullet_shooter = shooter;
    created_time = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();
    active = true;
}