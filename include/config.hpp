#ifndef CONFIG_HPP
#define CONFIG_HPP

namespace GameConfig {
    inline constexpr int WINDOW_WIDTH = 512;
    inline constexpr int WINDOW_HEIGHT = 1024;
    inline constexpr const char* WINDOW_TITLE = "POST-ouhou-ECH";

    inline constexpr float playerSpeed = 0.02f;
	inline constexpr float FIXED_DELTATIME = 0.05f;

    inline constexpr float POSITION_UPPER_LIMIT = 0.9f;
    inline constexpr float POSITION_LOWER_LIMIT = -0.9f;
    inline constexpr float POSITION_LEFT_LIMIT = -0.8f;
    inline constexpr float POSITION_RIGHT_LIMIT = 0.8f;
}

#endif // CONFIG_HPP    