#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <glm/glm.hpp>
#include "config.hpp"

namespace Utility {
inline glm::vec3 getNormalizedDirection(const glm::vec3 &direction,
                                        float magnitude = 1.0f) {
  if (glm::length(direction) != 0.0f) {
    return (direction / glm::length(direction)) * magnitude;
  }
  return direction;
}

inline bool isInRenderBounds(const glm::vec3 &pos) {
  return (pos.x > GameConfig::GAME_RENDER_LEFT_LIMIT &&
          pos.x < GameConfig::GAME_RENDER_RIGHT_LIMIT &&
          pos.y > GameConfig::GAME_RENDER_LOWER_LIMIT &&
          pos.y < GameConfig::GAME_RENDER_UPPER_LIMIT);
}
}; // namespace Utility
#endif // UTILITY_HPP