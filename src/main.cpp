#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "config.hpp"
#include "game.hpp"

Game::Game game;

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(GameConfig::WINDOW_WIDTH, GameConfig::WINDOW_HEIGHT);
    glutCreateWindow(GameConfig::WINDOW_TITLE);
    glutSetKeyRepeat(GLUT_KEY_REPEAT_ON);
    glewInit();

    glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(glm::ortho(
        0.0f, static_cast<float>(GameConfig::WINDOW_HEIGHT),
        0.0f, static_cast<float>(GameConfig::WINDOW_WIDTH),
        -1.0f, 1.0f
    )));

    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc([]() {
        game.draw();
    });
    glutKeyboardFunc([](unsigned char key, int x, int y) {
        game.keyEvent(key, x, y);
    });

    glutKeyboardUpFunc([](unsigned char key, int x, int y) {
        game.keyUpEvent(key, x, y);
    });
    glutMainLoop();
}  