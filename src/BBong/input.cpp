#include <BBong/input.hpp>

namespace BBong {
void Input::keyEvent(unsigned char key, int x, int y) {
  switch (key) {
  case 'w':
    playerMoveVec.y++;
    break;
  case 's':
    playerMoveVec.y--;
    break;
  case 'a':
    playerMoveVec.x--;
    break;
  case 'd':
    playerMoveVec.x++;
    break;
  case 'q':
    glutSetKeyRepeat(GLUT_KEY_REPEAT_DEFAULT);
    exit(0);
  case ' ':
    isShooting = true;
    break;
  case 'e':
    switch (projectionMode) {
    case PERSPECTIVE:
      projectionMode = ORTHOGRAPHIC;
      std::cerr << "Switched to ORTHOGRAPHIC mode." << std::endl;
      break;
    case ORTHOGRAPHIC:
      projectionMode = TPV_TOPVIEW;
      std::cerr << "Switched to TPV_TOPVIEW mode." << std::endl;  
      break;
    case TPV_TOPVIEW:
      projectionMode = PERSPECTIVE;
      std::cerr << "Switched to PERSPECTIVE mode." << std::endl;
      break;
    }
    break;
  case 'r':
    switch (graphicStyleMode) {
    case WIREFRAME:
      graphicStyleMode = SOLID;
      std::cerr << "Switched to SOLID mode." << std::endl;
      break;
    case SOLID:
      graphicStyleMode = WIREFRAME;
      std::cerr << "Switched to WIREFRAME mode." << std::endl;
      break;
    }
    GraphicsManager::getInstance().update();
    break;
  default:
    break;
  }
}

void Input::keyUpEvent(unsigned char key, int x, int y) {
  switch (key) {
  case 'w':
    playerMoveVec.y--;
    break;
  case 's':
    playerMoveVec.y++;
    break;
  case 'a':
    playerMoveVec.x++;
    break;
  case 'd':
    playerMoveVec.x--;
    break;
  case ' ':
    isShooting = false;
    break;
  default:
    break;
  }
}
} // namespace BBong