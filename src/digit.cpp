#include "digit.hpp"

std::vector<glm::vec3> Digit::getDigitVertices(int digit) {
    switch (digit) {
        case 0:
            return std::vector<glm::vec3> {
                glm::vec3(-GameConfig::FONT_DIGIT_SIZE, +4 * GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(-2 * GameConfig::FONT_DIGIT_SIZE, +.00f, +.00f),
                glm::vec3(-GameConfig::FONT_DIGIT_SIZE, -4 * GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(+GameConfig::FONT_DIGIT_SIZE, -4 * GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(+2 * GameConfig::FONT_DIGIT_SIZE, +.00f, +.00f),
                glm::vec3(+GameConfig::FONT_DIGIT_SIZE, +4 * GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(-GameConfig::FONT_DIGIT_SIZE, +4 * GameConfig::FONT_DIGIT_SIZE, +.00f)
            };
        case 1:
            return std::vector<glm::vec3> {
                glm::vec3(-2 * GameConfig::FONT_DIGIT_SIZE, +2 * GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(+GameConfig::FONT_DIGIT_SIZE, +4 * GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(+GameConfig::FONT_DIGIT_SIZE, -4 * GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(-2 * GameConfig::FONT_DIGIT_SIZE, -4 * GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(+2 * GameConfig::FONT_DIGIT_SIZE, -4 * GameConfig::FONT_DIGIT_SIZE, +.00f)
            };
        case 2:
            return std::vector<glm::vec3> {
                glm::vec3(-2 * GameConfig::FONT_DIGIT_SIZE, +GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(-GameConfig::FONT_DIGIT_SIZE, +4 * GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(+GameConfig::FONT_DIGIT_SIZE, +4 * GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(+2 * GameConfig::FONT_DIGIT_SIZE, +GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(-2 * GameConfig::FONT_DIGIT_SIZE, -4 * GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(+2 * GameConfig::FONT_DIGIT_SIZE, -4 * GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(+2 * GameConfig::FONT_DIGIT_SIZE, -3 * GameConfig::FONT_DIGIT_SIZE, +.00f)
            };
        case 3:
            return std::vector<glm::vec3> {
                glm::vec3(-2 * GameConfig::FONT_DIGIT_SIZE, +GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(-GameConfig::FONT_DIGIT_SIZE, +4 * GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(+GameConfig::FONT_DIGIT_SIZE, +4 * GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(+2 * GameConfig::FONT_DIGIT_SIZE, +GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(+.00f, +GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(+2 * GameConfig::FONT_DIGIT_SIZE, -2 * GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(+GameConfig::FONT_DIGIT_SIZE, -4 * GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(-GameConfig::FONT_DIGIT_SIZE, -4 * GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(-2 * GameConfig::FONT_DIGIT_SIZE, -2 * GameConfig::FONT_DIGIT_SIZE, +.00f)
            };
        case 4:
            return std::vector<glm::vec3> {
                glm::vec3(+2 * GameConfig::FONT_DIGIT_SIZE, -GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(-2 * GameConfig::FONT_DIGIT_SIZE, -GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(+GameConfig::FONT_DIGIT_SIZE, +4 * GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(+GameConfig::FONT_DIGIT_SIZE, -4 * GameConfig::FONT_DIGIT_SIZE, +.00f)
            };
        case 5: 
            return std::vector<glm::vec3> {
                glm::vec3(+GameConfig::FONT_DIGIT_SIZE, +4 * GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(-GameConfig::FONT_DIGIT_SIZE, +4 * GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(-2 * GameConfig::FONT_DIGIT_SIZE, +.00f, +.00f),
                glm::vec3(+.00f, +GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(+2 * GameConfig::FONT_DIGIT_SIZE, -GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(+GameConfig::FONT_DIGIT_SIZE, -4 * GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(-GameConfig::FONT_DIGIT_SIZE, -4 * GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(-2 * GameConfig::FONT_DIGIT_SIZE, -2 * GameConfig::FONT_DIGIT_SIZE, +.00f)
            };
        case 6:
            return std::vector<glm::vec3> {
                glm::vec3(+GameConfig::FONT_DIGIT_SIZE, +4 * GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(-GameConfig::FONT_DIGIT_SIZE, +4 * GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(-2 * GameConfig::FONT_DIGIT_SIZE, +.00f, +.00f),
                glm::vec3(+.00f, +GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(+2 * GameConfig::FONT_DIGIT_SIZE, -GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(+GameConfig::FONT_DIGIT_SIZE, -4 * GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(-GameConfig::FONT_DIGIT_SIZE, -4 * GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(-2 * GameConfig::FONT_DIGIT_SIZE, +.00f, +.00f),
            };
        case 7:
            return std::vector<glm::vec3> {
                glm::vec3(-2 * GameConfig::FONT_DIGIT_SIZE, +2 * GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(-2 * GameConfig::FONT_DIGIT_SIZE, +4 * GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(+2 * GameConfig::FONT_DIGIT_SIZE, +4 * GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(-GameConfig::FONT_DIGIT_SIZE, -4 * GameConfig::FONT_DIGIT_SIZE, +.00f)
            };
        case 8:
            return std::vector<glm::vec3> {
                glm::vec3(-2 * GameConfig::FONT_DIGIT_SIZE, +GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(-GameConfig::FONT_DIGIT_SIZE, +4 * GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(+GameConfig::FONT_DIGIT_SIZE, +4 * GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(+2 * GameConfig::FONT_DIGIT_SIZE, +GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(-2 * GameConfig::FONT_DIGIT_SIZE, -GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(-GameConfig::FONT_DIGIT_SIZE, -4 * GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(+GameConfig::FONT_DIGIT_SIZE, -4 * GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(+2 * GameConfig::FONT_DIGIT_SIZE, -GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(-2 * GameConfig::FONT_DIGIT_SIZE, +GameConfig::FONT_DIGIT_SIZE, +.00f)
            };
        case 9:
            return std::vector<glm::vec3> {
                glm::vec3(+2 * GameConfig::FONT_DIGIT_SIZE, +GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(+.00f, +.00f, +.00f),
                glm::vec3(-2 * GameConfig::FONT_DIGIT_SIZE, +GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(-GameConfig::FONT_DIGIT_SIZE, +4 * GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(+GameConfig::FONT_DIGIT_SIZE, +4 * GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(+2 * GameConfig::FONT_DIGIT_SIZE, +GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(+2 * GameConfig::FONT_DIGIT_SIZE, -GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(+GameConfig::FONT_DIGIT_SIZE, -4 * GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(-GameConfig::FONT_DIGIT_SIZE, -4 * GameConfig::FONT_DIGIT_SIZE, +.00f),
                glm::vec3(-2 * GameConfig::FONT_DIGIT_SIZE, -GameConfig::FONT_DIGIT_SIZE, +.00f)
            };
        default:
            throw std::invalid_argument("Digit must be in range [0, 9]");
    }
}
    
std::vector<glm::vec3> Digit::getDigitColors(int digit, const Shape::RGBColor& color) {
    switch (digit) {
        case 0:
            return std::vector<Shape::RGBColor>(7, color);
        case 1:
            return std::vector<Shape::RGBColor>(5, color);
        case 2:
            return std::vector<Shape::RGBColor>(7, color);
        case 3:
            return std::vector<Shape::RGBColor>(9, color);
        case 4:
            return std::vector<Shape::RGBColor>(4, color);
        case 5:
            return std::vector<Shape::RGBColor>(8, color);
        case 6:
            return std::vector<Shape::RGBColor>(8, color);
        case 7:
            return std::vector<Shape::RGBColor>(4, color);
        case 8:
            return std::vector<Shape::RGBColor>(9, color);
        case 9:
            return std::vector<Shape::RGBColor>(10, color);
        default:
            throw std::invalid_argument("Digit must be in range [0, 9]");
    }

}