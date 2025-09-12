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
    glewInit();

    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc([]() {
        game.draw();
    });
    glutKeyboardFunc([](unsigned char key, int x, int y) {
        game.keyEvent(key, x, y);
    });
    glutMainLoop();
}  