#include <BBong/inputmanager.hpp>

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
      projectionMode = TPV_TOPVIEW;
      std::cerr << "Switched to TPV_TOPVIEW mode." << std::endl;
      break;
    // case ORTHOGRAPHIC:
    //   projectionMode = TPV_TOPVIEW;
    //   std::cerr << "Switched to TPV_TOPVIEW mode." << std::endl;  
    //   break;
    case TPV_TOPVIEW:
      projectionMode = PERSPECTIVE;
      std::cerr << "Switched to PERSPECTIVE mode." << std::endl;
      break;
    // case PLAYER_VIEW:
    //   projectionMode = PERSPECTIVE;
    //   std::cerr << "Switched to PERSPECTIVE mode." << std::endl;
    //   break;
    }
    break;
  // case 'r':
  //   switch (graphicStyleMode) {
  //   case WIREFRAME:
  //     graphicStyleMode = SOLID;
  //     std::cerr << "Switched to SOLID mode." << std::endl;
  //     break;
  //   case SOLID:
  //     graphicStyleMode = HIDDEN_LINE_REMOVAL;
  //     std::cerr << "Switched to HIDDEN_LINE_REMOVAL mode." << std::endl;
  //     break;
  //   case HIDDEN_LINE_REMOVAL:
  //     graphicStyleMode = WIREFRAME;
  //     std::cerr << "Switched to WIREFRAME mode." << std::endl;
  //     break;
  //   }
  //   GraphicsManager::getInstance().update();
  //   break;
  case 'c':
    switch (shadingMode) {
    case GOURAUD:
      shadingMode = PHONG;
      std::cerr << "Switched to PHONG mode." << std::endl;
      break;
    case PHONG:
      shadingMode = PHONG_NORMAL_MAPPING;
      std::cerr << "Switched to PHONG_NORMAL_MAPPING mode." << std::endl;
      break;
    case PHONG_NORMAL_MAPPING:
      shadingMode = GOURAUD;
      std::cerr << "Switched to GOURAUD mode." << std::endl;
      break;
    }
    ShaderManager::getInstance().attachProgram("basic_shader");
    ShaderManager::getInstance().setUniformValue<int>(
      "basic_shader", "uIntShadingMode", shadingMode
    );
    ShaderManager::getInstance().detachProgram();
    break;
  case 't':
    boundingBoxVisible = !boundingBoxVisible;
    std::cerr << "Bounding Box Visibility: " 
              << (boundingBoxVisible ? "ON" : "OFF") << "." << std::endl;
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