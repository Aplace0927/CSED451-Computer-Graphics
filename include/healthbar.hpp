#ifndef HEALTHBAR_HPP
#define HEALTHBAR_HPP

#include "object.hpp"
#include "digit.hpp"
#include "shape.hpp"

namespace HealthBar {
    class HealthBar: public Object::Object<glm::vec3, Shape::RGBColor>{
    public:
        void update(time_t time) override;
        void fixedUpdate() override;

        HealthBar();
        HealthBar(const glm::vec3& position, int maxHealth);

        void setCurrentHealth(int health);
        int getCurrentHealth() const;
        int getMaxHealth() const;
    private:
        int maxHealth;
        int currentHealth;
    };
    
    std::vector<glm::vec3> createHealthBarShape(float gauge);
    std::vector<Shape::RGBColor> createHealthBarColors(float gauge);
}

#endif // HEALTHBAR_HPP