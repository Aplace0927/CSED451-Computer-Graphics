#ifndef DIGIT_HPP
#define DIGIT_HPP

#include "config.hpp"
#include "shape.hpp"
#include <glm/glm.hpp>
#include <stdexcept>
#include <vector>

namespace Digit {
std::vector<glm::vec3> getDigitVertices(int digit);
std::vector<Shape::RGBColor> getDigitColors(int digit,
                                            const Shape::RGBColor &color);
} // namespace Digit

Shape::Shape<glm::vec3, Shape::RGBColor> getWinVertices();
Shape::Shape<glm::vec3, Shape::RGBColor> getLoseVertices();
#endif // DIGIT_HPP