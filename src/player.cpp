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
    isShooting(false),
    healthBar(
        glm::vec3(GameConfig::PLAYER_DIGIT_X, GameConfig::PLAYER_DIGIT_Y, 0.0f),
        GameConfig::FONT_DIGIT_SIZE,
        glm::vec3(GameConfig::PLAYER_GAUGE_X, GameConfig::PLAYER_GAUGE_Y, 0.0f),
        GameConfig::PLAYER_GAUGE_WIDTH,
        GameConfig::PLAYER_GAUGE_HEIGHT,
        playerHealth
    )
{
    // Initialize other player state variables here if needed
	shootingCooldown = 0;
    bullets = ObjectPool::ObjectPool<Bullet::Bullet>();
	playerHealth = GameConfig::PLAYER_LIFE;
	isShooting = false;
	direction = glm::vec3(0.0f, 0.0f, 0.0f);
}

void Player::Player::update(time_t time) {
    if (!getStatus()) {
        return;
    }
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

    draw();
}

void Player::Player::fixedUpdate() {
    move(direction);

    glm::vec3 currentPos = getCenter();
    setPosition(glm::vec3(
        glm::clamp(currentPos.x, GameConfig::POSITION_LEFT_LIMIT, GameConfig::POSITION_RIGHT_LIMIT),
        glm::clamp(currentPos.y, GameConfig::POSITION_LOWER_LIMIT, GameConfig::POSITION_UPPER_LIMIT),
        currentPos.z
    ));
}