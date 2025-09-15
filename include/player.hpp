#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "object.hpp"

namespace Player {
    class Player : public Object::Object<glm::vec3, Shape::RGBColor> {
    public:
        Player();
    private:
        // Add player state variables here 
        int playerHealth;  
    };

    namespace BulletPattern {
        constexpr float BulletSpeed = 0.0001f;
        inline std::function<glm::vec3(glm::vec3, time_t)> straight_up() {
            return [](glm::vec3 origin, time_t time_elapsed) {
                float linear_speed = BulletSpeed * static_cast<float>(time_elapsed);
                return origin + glm::vec3(0.0f, linear_speed, 0.0f);
            };
        }
    }
};
#endif // PLAYER_HPP