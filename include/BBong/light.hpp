#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "component.hpp"
#include <glm/glm.hpp>

namespace BBong {

enum class LightType { Directional, Point };

class Light : public ClonableComponent<Light> {
public:
  explicit Light(GameObject *owner) : ClonableComponent(owner) {}
  Light(const Light &other) : ClonableComponent(nullptr) {}

  static void ResetFrame();

  LightType type = LightType::Point;

  glm::vec3 ambient = glm::vec3(0.1f);
  glm::vec3 diffuse = glm::vec3(1.0f);
  glm::vec3 specular = glm::vec3(1.0f);

  float constant = 1.0f;
  float linear = 0.09f;
  float quadratic = 0.032f;

  void setDirectional(const glm::vec3 &amb, const glm::vec3 &diff,
                      const glm::vec3 &spec);
  void setPoint(const glm::vec3 &amb, const glm::vec3 &diff,
                const glm::vec3 &spec, float c = 1.0f, float l = 0.09f,
                float q = 0.032f);

  glm::vec3 getDirection() const;

private:
  void lateUpdate() override;
};

} // namespace BBong
#endif // LIGHT_HPP