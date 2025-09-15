#ifndef GAME_HPP
#define GAME_HPP

#include "player.hpp"
#include "singleton.hpp"

namespace Game {
    class Game : public Singleton::Singleton<Game> {
    public:
        Game();
		~Game();
        void keyEvent(unsigned char key, int x, int y);
    private:
        Player::Player player; 
    };
};

#endif // GAME_HPP