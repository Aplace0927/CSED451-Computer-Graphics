#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <glm/glm.hpp>
#include <chrono>
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

inline time_t getCurrentTimeMS() {
  return std::chrono::duration_cast<std::chrono::milliseconds>(
             std::chrono::system_clock::now().time_since_epoch())
      .count();
}

template <typename T>
inline T getPhaseGenerator(double period, double phaseDeg = 0.0) {
  return static_cast<T>(
      fmod(
          static_cast<double>(
              getCurrentTimeMS()
          ) * period + phaseDeg,
          360.0
      )
  );
}

template <typename T>
inline T getPhaseOscillator(double minDeg, double maxDeg, double period) {
  return static_cast<T>(
      fmod(maxDeg - minDeg, 360.0) / 2.0 * cos(
          glm::radians(
              static_cast<double>(
                  getCurrentTimeMS()
              ) * period
          )
      ) + (maxDeg - minDeg)
  );
}
}; // namespace Utility
#endif // UTILITY_HPP