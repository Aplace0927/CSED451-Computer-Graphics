#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <functional>
#include <chrono>

#include "player.hpp"
#include "enemy.hpp"
#include "movement.hpp"
#include "bullet.hpp"
#include "singleton.hpp"
#include "objectpool.hpp"

namespace Game {
    class Game : public Singleton::Singleton<Game> {
    public:
        Game();
		~Game();
        void keyEvent(unsigned char key, int x, int y);
        void keyUpEvent(unsigned char key, int x, int y);
    private:
        Player::Player player;
        glm::vec3 playerMoveVec;

        Enemy::Enemy enemy;
        
        ObjectPool::ObjectPool<Bullet::Bullet> bullets;
    };
};

#endif // GAME_HPP