#ifndef UTILS_HPP
#define UTILS_HPP

#include <glm/glm.hpp>

namespace Utils {
    inline glm::vec3 getNormalizedDirection(const glm::vec3& direction, float magnitude = 1.0f) {
        if (glm::length(direction) != 0.0f) {
            return (direction / glm::length(direction)) * magnitude;
        }
        return direction;
    }
};

#endif // MOVEMENT_HPP