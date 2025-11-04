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