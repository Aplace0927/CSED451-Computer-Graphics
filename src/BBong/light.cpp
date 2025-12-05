#include "BBong/light.hpp"
#include "BBong/transform.hpp"
#include "BBong/gameobject.hpp"
#include "BBong/shadermanager.hpp"
#include <glm/gtx/quaternion.hpp>
#include <string>

namespace BBong {

static int s_pointLightIndex = 0;

void Light::ResetFrame() { s_pointLightIndex = 0; }

void Light::lateUpdate() {
  ShaderManager &shader = ShaderManager::getInstance();
  shader.attachProgram("basic_shader");

  if (type == LightType::Directional) {
    glm::vec3 dir = getDirection();
    shader.setUniformValue<glm::vec3>("basic_shader", "dirLight.direction", dir);
    shader.setUniformValue<glm::vec3>("basic_shader", "dirLight.ambient", ambient);
    shader.setUniformValue<glm::vec3>("basic_shader", "dirLight.diffuse", diffuse);
    shader.setUniformValue<glm::vec3>("basic_shader", "dirLight.specular", specular);
  } else if (type == LightType::Point) {
    std::string base = "pointLights[" + std::to_string(s_pointLightIndex) + "]";
    glm::vec3 pos = transform->getWorldPosition();

    shader.setUniformValue<glm::vec3>("basic_shader", base + ".position", pos);
    shader.setUniformValue<float>("basic_shader", base + ".constant", constant);
    shader.setUniformValue<float>("basic_shader", base + ".linear", linear);
    shader.setUniformValue<float>("basic_shader", base + ".quadratic", quadratic);
    shader.setUniformValue<glm::vec3>("basic_shader", base + ".ambient", ambient);
    shader.setUniformValue<glm::vec3>("basic_shader", base + ".diffuse", diffuse);
    shader.setUniformValue<glm::vec3>("basic_shader", base + ".specular", specular);

    s_pointLightIndex++;
  }

  shader.detachProgram();
}

void Light::setDirectional(const glm::vec3 &amb, const glm::vec3 &diff,
                           const glm::vec3 &spec) {
  type = LightType::Directional;
  ambient = amb;
  diffuse = diff;
  specular = spec;
}

void Light::setPoint(const glm::vec3 &amb, const glm::vec3 &diff,
                     const glm::vec3 &spec, float c, float l, float q) {
  type = LightType::Point;
  ambient = amb;
  diffuse = diff;
  specular = spec;
  constant = c;
  linear = l;
  quadratic = q;
}

glm::vec3 Light::getDirection() const {
  glm::vec3 forward = glm::vec3(0.0f, 0.0f, -1.0f);
  return transform->getRotation() * forward;
}
} // namespace BBong