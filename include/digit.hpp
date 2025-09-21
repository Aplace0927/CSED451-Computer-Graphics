#ifndef DIGIT_HPP
#define DIGIT_HPP

#include <vector>
#include <glm/glm.hpp>
#include <stdexcept>
#include "shape.hpp"
#include "config.hpp"

namespace Digit {
    std::vector<glm::vec3> getDigitVertices(int digit);
    std::vector<Shape::RGBColor> getDigitColors(int digit, const Shape::RGBColor& color);
}

#endif // DIGIT_HPP