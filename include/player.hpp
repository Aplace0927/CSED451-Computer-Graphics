#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "object.hpp"
#include "config.hpp"

namespace Player {
    class Player : public Object::Object<glm::vec3, Shape::RGBColor> {
    public:
        Player();
		void fixedUpdate() override;
        void setDirection(const glm::vec3& input) {
            direction = input;
		}
        void shooting(bool shooting) {
            isShooting = shooting;
        }
    private:
        // Add player state variables here 
        int playerHealth;
        bool isShooting;
		glm::vec3 direction;
    };
};
#endif // PLAYER_HPP