#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "config.hpp"

namespace GameState {
enum GameState { PLAYING, WIN, LOSE };
struct GameStateHolder {
    GameState currentState = PLAYING;
    unsigned int enemyLeft = GameConfig::INITIAL_ENEMY_COUNT;
};
}

#endif // GAMESTATE_HPP