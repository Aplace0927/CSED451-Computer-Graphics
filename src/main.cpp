#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "BBong/graphicsmanager.hpp"
#include "BBong/inputmanager.hpp"
#include "config.hpp"
#include "shaderutility.hpp"
#include "game.hpp"

int main(int argc, char **argv) {
  BBong::Game::getInstance().Init();

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(GameConfig::WINDOW_WIDTH, GameConfig::WINDOW_HEIGHT);
  glutCreateWindow(GameConfig::WINDOW_TITLE);
  glewInit();

  std::vector<ShaderInfo> shaders = {
      {"../src/shader/vert_shader.glsl", GL_VERTEX_SHADER},
      {"../src/shader/frag_shader.glsl", GL_FRAGMENT_SHADER},
  };

  initializeShader(shaders);

  glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);

  glEnable(GL_DEPTH_TEST | GL_TEXTURE_2D);

  glutReshapeFunc([](int x, int y) {
    BBong::GraphicsManager::getInstance().reshape(x, y);
  });

  glutDisplayFunc([]() { BBong::GraphicsManager::getInstance().update(); });

  glutKeyboardFunc([](unsigned char key, int x, int y) {
    BBong::Input::getInstance().keyEvent(key, x, y);
  });

  glutKeyboardUpFunc([](unsigned char key, int x, int y) {
    BBong::Input::getInstance().keyUpEvent(key, x, y);
  });
  glutMainLoop();
}