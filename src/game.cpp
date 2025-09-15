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
            player.move(glm::vec3(0.0f, 0.02f, 0.0f));
            break;
        case 's':
        case 'S':
            player.move(glm::vec3(0.0f, -0.02f, 0.0f));
            break;
        case 'a':
        case 'A':
            player.move(glm::vec3(-0.02f, 0.0f, 0.0f));
            break;
        case 'd':
        case 'D':
            player.move(glm::vec3(0.02f, 0.0f, 0.0f));
            break;
        case 'q':
        case 'Q':
            player.rotate(
                glm::vec3(0.0f, 0.0f, glm::radians(-5.0f)),
                player.getCenter()
            );
            break;
        case 'e':
        case 'E':
            player.rotate(
                glm::vec3(0.0f, 0.0f, glm::radians(5.0f)),
                player.getCenter()
            );
            break;
        default:
            break;
    }
}
