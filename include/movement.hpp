#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP

#include <glm/glm.hpp>

namespace Movement {
    inline glm::vec3 getNormalizedDirection(const glm::vec3& direction, float magnitude = 1.0f) {
        if (glm::length(direction) != 0.0f) {
            return (direction / glm::length(direction)) * magnitude;
        }
        return direction;
    }
};

#endif // MOVEMENT_HPP