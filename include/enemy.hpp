#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <cmath>

#include "object.hpp"
#include "objectpool.hpp"
#include "bullet.hpp"
#include "enemypatterns.hpp"

namespace Enemy {
    class Enemy : public Object::Object<glm::vec3, Shape::RGBColor> {
    public:
        Enemy();
        void update(time_t time) override;
        void fixedUpdate() override;
    private:
        // Add enemy state variables here 
        int enemyHealth;
		std::vector<enemypatterns::IPattern> attackPatterns;
        ObjectPool::ObjectPool<Bullet::Bullet> bullets;
    };
};
#endif // ENEMY_HPP