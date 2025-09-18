#include "player.hpp"

Player::Player::Player()
    : Object::Object(
        // Center at origin
        glm::vec3(0.0f, -0.5f, 0.0f), 
        Shape::Shape<glm::vec3, Shape::RGBColor>(    
            // subshapes: vector of subshapes, each subshape is a vector of vertices
            std::vector<std::vector<glm::vec3>>{
                {
                    glm::vec3(0.0f, 0.05f, 0.0f),
                    glm::vec3(-0.1f, -0.05f, 0.0f),
                    glm::vec3(0.1f, -0.05f, 0.0f)
                }
            },
            // colors: vector of color sets, each set is a vector of colors for the subshape
            std::vector<std::vector<Shape::RGBColor>>{
                {
                    Shape::RGBColor(1.0f, 1.0f, 0.0f),
                    Shape::RGBColor(0.0f, 1.0f, 1.0f),
                    Shape::RGBColor(1.0f, 0.0f, 1.0f)
                }
            },
            // drawMethod: vector of draw methods for each subshape
            std::vector<unsigned int>{ GL_TRIANGLES }
        )
    ),
    playerHealth(5),
    isShooting(false)
{
	shootingCooldown = 0;
	direction = glm::vec3(0.0f, 0.0f, 0.0f);
    bullets = ObjectPool::ObjectPool<Bullet::Bullet>();
    // Initialize other player state variables here if needed
}

void Player::Player::update(time_t time) {
    if (isShooting && time - shootingCooldown >= GameConfig::SHOOTING_COOLDOWN_MS) {
        Bullet::Bullet* newBullet = bullets.acquire();
        newBullet->activate(
            getCenter() + glm::vec3(0.0f, 0.05f, 0.0f),
            BulletPattern::Player::straight_up(),
            Bullet::BulletType::PLAYER,
            [this, newBullet]() { this->bullets.release(newBullet); },
            bulletHitDetectFunction,
            bulletHitEventFunction
        );
        shootingCooldown = time;
    }

    for (Bullet::Bullet* bullet: bullets.pool) {
        glm::vec3 bulletVec = bullet->getCenter();
        if (
            GameConfig::GAME_RENDER_LOWER_LIMIT < bulletVec.y && bulletVec.y < GameConfig::GAME_RENDER_UPPER_LIMIT &&
            GameConfig::GAME_RENDER_LEFT_LIMIT < bulletVec.x && bulletVec.x < GameConfig::GAME_RENDER_RIGHT_LIMIT
        ) {
            continue;
        }
        if (bullet->getStatus()) {
            bullet->callReleaseFunction();
        }
    }

    glm::vec3 currentPos = getCenter();
    setPosition(glm::vec3(
        glm::clamp(currentPos.x, GameConfig::POSITION_LEFT_LIMIT, GameConfig::POSITION_RIGHT_LIMIT),
        glm::clamp(currentPos.y, GameConfig::POSITION_LOWER_LIMIT, GameConfig::POSITION_UPPER_LIMIT),
        currentPos.z
    ));
    draw();
}

void Player::Player::fixedUpdate() {
    move(direction);
}