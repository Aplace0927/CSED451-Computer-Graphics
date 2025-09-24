#ifndef CONFIG_HPP
#define CONFIG_HPP

namespace GameConfig {
inline constexpr int WINDOW_WIDTH = 512;
inline constexpr int WINDOW_HEIGHT = 1024;
inline constexpr const char *WINDOW_TITLE = "POST-ouhou-ECH";

inline constexpr float PLAYER_SPEED = 10.0f;
inline constexpr float FIXED_DELTATIME = 0.02f;

inline constexpr float POSITION_UPPER_LIMIT = WINDOW_HEIGHT * 0.425f;
inline constexpr float POSITION_LOWER_LIMIT = -WINDOW_HEIGHT * 0.425f;
inline constexpr float POSITION_LEFT_LIMIT = -WINDOW_WIDTH * 0.4f;
inline constexpr float POSITION_RIGHT_LIMIT = WINDOW_WIDTH * 0.4f;

inline constexpr float GAME_RENDER_UPPER_LIMIT = WINDOW_HEIGHT;
inline constexpr float GAME_RENDER_LOWER_LIMIT = -WINDOW_HEIGHT;
inline constexpr float GAME_RENDER_LEFT_LIMIT = -WINDOW_WIDTH;
inline constexpr float GAME_RENDER_RIGHT_LIMIT = WINDOW_WIDTH;

inline constexpr size_t DEFAULT_POOL_SIZE = 0x10;

inline constexpr float SHOOTING_COOLDOWN_MS = 0.05;

inline constexpr float FONT_DIGIT_SIZE = 2.0f;
inline constexpr float BIG_FONT_SIZE = 8.0f;
inline constexpr float DIGIT_SPACING = FONT_DIGIT_SIZE * 6;

inline constexpr int ENEMY_LIFE = 100;
inline constexpr float ENEMY_DIGIT_X = -WINDOW_WIDTH * 0.45f;
inline constexpr float ENEMY_DIGIT_Y = WINDOW_HEIGHT * 0.45f;
inline constexpr float ENEMY_GAUGE_X = ENEMY_DIGIT_X + DIGIT_SPACING * 5;
inline constexpr float ENEMY_GAUGE_Y = ENEMY_DIGIT_Y - DIGIT_SPACING / 2;
inline constexpr float ENEMY_GAUGE_WIDTH = WINDOW_WIDTH * 0.8f;
inline constexpr float ENEMY_GAUGE_HEIGHT = FONT_DIGIT_SIZE * 4;
inline constexpr float ENEMY_BULLET_COLOR[3] = {
    (float)0xFF / 0xFF, (float)0xC6 / 0xFF, (float)0x39 / 0xFF};

inline constexpr int PLAYER_LIFE = 10;
inline constexpr float PLAYER_DIGIT_X = -WINDOW_WIDTH * 0.45f;
inline constexpr float PLAYER_DIGIT_Y = -WINDOW_HEIGHT * 0.45f;
inline constexpr float PLAYER_GAUGE_X = PLAYER_DIGIT_X + DIGIT_SPACING * 5;
inline constexpr float PLAYER_GAUGE_Y = PLAYER_DIGIT_Y - DIGIT_SPACING / 2;
inline constexpr float PLAYER_GAUGE_WIDTH = WINDOW_WIDTH * 0.8f;
inline constexpr float PLAYER_GAUGE_HEIGHT = FONT_DIGIT_SIZE * 4;
inline constexpr float PLAYER_BULLET_COLOR[3] = {
    (float)0x50 / 0xFF, (float)0xD0 / 0xFF, (float)0xD0 / 0xFF};

inline constexpr float GAUGE_FULL_COLOR[3] = {0.0f, 1.0f, 0.0f};
inline constexpr float GAUGE_EMPTY_COLOR[3] = {1.0f, 0.0f, 0.0f};

inline constexpr float WIN_TEXT_COLOR[3] = {
    (float)0xFF / 0xFF, (float)0xFF / 0xFF, (float)0xFF / 0xFF};
inline constexpr float WIN_BG_COLOR[3] = {
    (float)0x5C / 0xFF, (float)0x7C / 0xFF, (float)0xFA / 0xFF};

inline constexpr float LOSE_TEXT_COLOR[3] = {
    (float)0xFF / 0xFF, (float)0xFF / 0xFF, (float)0xFF / 0xFF};
inline constexpr float LOSE_BG_COLOR[3] = {
    (float)0xF0 / 0xFF, (float)0x65 / 0xFF, (float)0x95 / 0xFF};
} // namespace GameConfig
#endif // CONFIG_HPP