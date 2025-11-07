#ifndef INPUT_HPP
#define INPUT_HPP

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include "BBong/singleton.hpp"
#include "BBong/graphicsmanager.hpp"
#include "utility.hpp"

namespace BBong {
class Input : public Singleton<Input> {
public:
  Input()
    : playerMoveVec(0.0f, 0.0f, 0.0f),
      isShooting(false)
  {}
  ~Input(){}
  void keyEvent(unsigned char key, int x, int y);
  void keyUpEvent(unsigned char key, int x, int y);

  glm::vec3 playerMoveVec;
  bool isShooting;

  enum ProjectionMode {
    PERSPECTIVE,
    ORTHOGRAPHIC,
    TPV_TOPVIEW
  };
  enum GraphicStyleMode {
    WIREFRAME,
    SOLID,
  };

  ProjectionMode projectionMode = PERSPECTIVE;
  GraphicStyleMode graphicStyleMode = SOLID;
  bool boundingBoxVisible = false;
};
}; // namespace Input

#endif // INPUT_HPP