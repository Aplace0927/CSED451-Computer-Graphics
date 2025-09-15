#include "bullet.hpp"

Bullet::Bullet::Bullet(
    glm::vec3 bullet_origin,
    std::function<glm::vec3(glm::vec3, time_t)> movement_pattern, 
    BulletType bullet_shooter
): 
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
    bullet_origin(bullet_origin),
    movement_pattern(movement_pattern),
    bullet_shooter(bullet_shooter),
    created_time(
        std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
        ).count()
    ) { }

void Bullet::Bullet::draw(time_t current_time) {
    move(movement_pattern(bullet_origin, current_time - created_time) - bullet_origin);
    Object::draw();
}