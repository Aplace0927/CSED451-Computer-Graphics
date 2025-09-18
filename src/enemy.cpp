#include "enemy.hpp"

Enemy::Enemy::Enemy()
    : Object::Object(
        // Center at origin
        glm::vec3(0.0f, +0.5f, 0.0f), 
        Shape::Shape<glm::vec3, Shape::RGBColor>(    
            // subshapes: vector of subshapes, each subshape is a vector of vertices
            std::vector<std::vector<glm::vec3>>{
                {
                    glm::vec3(-0.1f, 0.0f, 0.0f),
                    glm::vec3(-0.05f, 0.05f, 0.0f),
                    glm::vec3( 0.05f, 0.05f, 0.0f),
                    glm::vec3( 0.1f, 0.0f, 0.0f),
                    glm::vec3( 0.05f, -0.05f, 0.0f),
                    glm::vec3(-0.05f, -0.05f, 0.0f),
                    glm::vec3(-0.1f, 0.0f, 0.0f),
                }
            },
            // colors: vector of color sets, each set is a vector of colors for the subshape
            std::vector<std::vector<Shape::RGBColor>>{
                {
                    Shape::RGBColor(1.0f, 0.0f, 0.0f),
                    Shape::RGBColor(1.0f, 0.0f, 0.0f),
                    Shape::RGBColor(1.0f, 0.0f, 0.0f),
                    Shape::RGBColor(1.0f, 0.0f, 0.0f),
                    Shape::RGBColor(1.0f, 0.0f, 0.0f),
                    Shape::RGBColor(1.0f, 0.0f, 0.0f),
                    Shape::RGBColor(1.0f, 0.0f, 0.0f),
                }
            },
            // drawMethod: vector of draw methods for each subshape
            std::vector<unsigned int>{ GL_TRIANGLE_FAN }
        )
    ),
    enemyHealth(5)
{
    bullets = ObjectPool::ObjectPool<Bullet::Bullet>();
    // Initialize other enemy state variables here if needed
}

void Enemy::Enemy::update(time_t time) {
    draw();
    return;
    // Implement enemy behavior here
}

void Enemy::Enemy::fixedUpdate() {
    return;
    // Implement enemy behavior here
}