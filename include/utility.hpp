#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <glm/glm.hpp>
#include <chrono>
#include "config.hpp"

namespace Utility {
extern float DeltaTime;
extern float FixedDeltaTime;

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

inline time_t getCurrentTimeMS() {
  return std::chrono::duration_cast<std::chrono::milliseconds>(
             std::chrono::system_clock::now().time_since_epoch())
      .count();
}
}; // namespace Utility
#endif // UTILITY_HPP