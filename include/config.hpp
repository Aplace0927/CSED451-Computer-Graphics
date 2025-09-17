#ifndef CONFIG_HPP
#define CONFIG_HPP

namespace GameConfig {
    inline constexpr int WINDOW_WIDTH = 512;
    inline constexpr int WINDOW_HEIGHT = 1024;
    inline constexpr const char* WINDOW_TITLE = "POST-ouhou-ECH";

    inline constexpr float PLAYER_SPEED = 0.02f;
	inline constexpr float FIXED_DELTATIME = 0.02f;

    inline constexpr float POSITION_UPPER_LIMIT = 0.9f;
    inline constexpr float POSITION_LOWER_LIMIT = -0.9f;
    inline constexpr float POSITION_LEFT_LIMIT = -0.8f;
    inline constexpr float POSITION_RIGHT_LIMIT = 0.8f;

    inline constexpr float GAME_RENDER_UPPER_LIMIT = 3.0f;
    inline constexpr float GAME_RENDER_LOWER_LIMIT = -3.0f;
    inline constexpr float GAME_RENDER_LEFT_LIMIT = -3.0f;
    inline constexpr float GAME_RENDER_RIGHT_LIMIT = 3.0f;

    inline constexpr size_t DEFAULT_POOL_SIZE = 0x100;

    inline constexpr time_t SHOOTING_COOLDOWN_MS = 50;
}

#endif // CONFIG_HPP    