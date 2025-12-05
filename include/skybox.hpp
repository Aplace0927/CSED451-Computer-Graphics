#ifndef SKYBOX_HPP
#define SKYBOX_HPP

#include <array>
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "BBong/component.hpp"
#include "BBong/graphicsmanager.hpp"
#include "BBong/shadermanager.hpp"

namespace BBong {

// Simple Skybox component: creates a cubemap and renders a unit cube
class Skybox : public ClonableComponent<Skybox> {
public:
  explicit Skybox(GameObject *owner);
  Skybox(const Skybox &other);
  ~Skybox() override;

  // Provide 6 face file paths in order: +X, -X, +Y, -Y, +Z, -Z
  void setCubemapFaces(const std::array<std::string, 6> &faces);

  // Optionally override alias if a different shader name is used
  void setShaderAlias(const std::string &alias) { shaderAlias = alias; }

protected:
  void renderUpdate() override;

private:
  void initGeometry();
  void destroyGeometry();
  GLuint loadCubemap(const std::array<std::string, 6> &faces);

private:
  GLuint vao = 0;
  GLuint vbo = 0;
  GLuint cubemapTex = 0;
  std::string shaderAlias = "skybox_shader";
  std::array<std::string, 6> facePaths{};
};
} // namespace BBong

#endif // SKYBOX_HPP
