#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <cmath>

#include "object.hpp"

namespace Enemy {
    class Enemy : public Object::Object<glm::vec3, Shape::RGBColor> {
    public:
        Enemy();
    private:
        // Add enemy state variables here 
        int enemyHealth;
    };
};
#endif // ENEMY_HPP