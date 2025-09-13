#include "game.hpp"
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>

Game::Game::Game() {
    player = Player::Player();
}

void Game::Game::draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    player.draw();
    //!TODO: add game objects drawing here
    glutSwapBuffers();
    glutPostRedisplay();
}

void Game::Game::keyEvent(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
        case 'W':
            player.update({0.0f, 0.02f, 0.0f});
            break;
        case 's':
        case 'S':
            player.update({0.0f, -0.02f, 0.0f});
            break;
        case 'a':
        case 'A':
            player.update({-0.02f, 0.0f, 0.0f});
            break;
        case 'd':
        case 'D':
            player.update({0.02f, 0.0f, 0.0f});
            break;
        default:
            break;
    }
}
