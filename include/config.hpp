#ifndef CONFIG_HPP
#define CONFIG_HPP

namespace GameConfig {
    inline constexpr int WINDOW_WIDTH = 512;
    inline constexpr int WINDOW_HEIGHT = 1024;
    inline constexpr const char* WINDOW_TITLE = "POST-ouhou-ECH";

    inline constexpr float PLAYER_SPEED = 0.02f;
	inline constexpr float FIXED_DELTATIME = 0.02f;

    inline constexpr float POSITION_UPPER_LIMIT = 0.9f;
    inline constexpr float POSITION_LOWER_LIMIT = -0.85f;
    inline constexpr float POSITION_LEFT_LIMIT = -0.8f;
    inline constexpr float POSITION_RIGHT_LIMIT = 0.8f;

    inline constexpr float GAME_RENDER_UPPER_LIMIT = 3.0f;
    inline constexpr float GAME_RENDER_LOWER_LIMIT = -3.0f;
    inline constexpr float GAME_RENDER_LEFT_LIMIT = -3.0f;
    inline constexpr float GAME_RENDER_RIGHT_LIMIT = 3.0f;

    inline constexpr size_t DEFAULT_POOL_SIZE = 0x10;

    inline constexpr time_t SHOOTING_COOLDOWN_MS = 50;

    inline constexpr float FONT_DIGIT_SIZE = .005f;
    inline constexpr float DIGIT_SPACING = FONT_DIGIT_SIZE * 6;

    inline constexpr int ENEMY_LIFE = 100;
    inline constexpr float ENEMY_DIGIT_X = -0.9f;
    inline constexpr float ENEMY_DIGIT_Y = 0.9f;
    inline constexpr float ENEMY_GAUGE_X = ENEMY_DIGIT_X + DIGIT_SPACING * 5;
    inline constexpr float ENEMY_GAUGE_Y = ENEMY_DIGIT_Y;
    inline constexpr float ENEMY_GAUGE_WIDTH = 1.6f;
    inline constexpr float ENEMY_GAUGE_HEIGHT = FONT_DIGIT_SIZE * 4;


    inline constexpr int PLAYER_LIFE = 10;
    inline constexpr float PLAYER_DIGIT_X = -0.9f;
    inline constexpr float PLAYER_DIGIT_Y = -0.95f;
    inline constexpr float PLAYER_GAUGE_X = PLAYER_DIGIT_X + DIGIT_SPACING * 5;
    inline constexpr float PLAYER_GAUGE_Y = PLAYER_DIGIT_Y;
    inline constexpr float PLAYER_GAUGE_WIDTH = 1.6f;
    inline constexpr float PLAYER_GAUGE_HEIGHT = FONT_DIGIT_SIZE * 4;

    inline constexpr float GAUGE_FULL_COLOR[3] = {0.0f, 1.0f, 0.0f};
    inline constexpr float GAUGE_EMPTY_COLOR[3] = {1.0f, 0.0f, 0.0f};
}

#endif // CONFIG_HPP    