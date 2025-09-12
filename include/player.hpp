#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "object.hpp"

namespace Player {
    class Player : public Object::Object<float, 3, Shape::RGBColor> {
    public:
        Player();
    private:
        // Add player state variables here 
        int playerHealth;  
    };
};
#endif // PLAYER_HPP