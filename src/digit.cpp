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

Shape::Shape<glm::vec3, Shape::RGBColor> getWinVertices() {
    return Shape::Shape<glm::vec3, Shape::RGBColor>(
        std::vector<std::vector<glm::vec3>>{
            {
                glm::vec3(-6 * GameConfig::BIG_FONT_SIZE,  6 * GameConfig::BIG_FONT_SIZE, 0.5f),
                glm::vec3( 6 * GameConfig::BIG_FONT_SIZE,  6 * GameConfig::BIG_FONT_SIZE, 0.5f),
                glm::vec3( 6 * GameConfig::BIG_FONT_SIZE, -6 * GameConfig::BIG_FONT_SIZE, 0.5f),
                glm::vec3(-6 * GameConfig::BIG_FONT_SIZE, -6 * GameConfig::BIG_FONT_SIZE, 0.5f),

            },
            {
                glm::vec3(-4 * GameConfig::BIG_FONT_SIZE, -4 * GameConfig::BIG_FONT_SIZE, 1.0f),
                glm::vec3(-3 * GameConfig::BIG_FONT_SIZE, -2 * GameConfig::BIG_FONT_SIZE, 1.0f),
                glm::vec3(-3 * GameConfig::BIG_FONT_SIZE,  4 * GameConfig::BIG_FONT_SIZE, 1.0f),
                glm::vec3(-GameConfig::BIG_FONT_SIZE,  4 * GameConfig::BIG_FONT_SIZE, 1.0f),
                glm::vec3(-GameConfig::BIG_FONT_SIZE,  2 * GameConfig::BIG_FONT_SIZE, 1.0f),
                glm::vec3(-3 * GameConfig::BIG_FONT_SIZE,  2 * GameConfig::BIG_FONT_SIZE, 1.0f),
                glm::vec3(-GameConfig::BIG_FONT_SIZE,  2 * GameConfig::BIG_FONT_SIZE, 1.0f),
                glm::vec3(-GameConfig::BIG_FONT_SIZE,  0.0f, 1.0f),
                glm::vec3(-3 * GameConfig::BIG_FONT_SIZE,  0.0f, 1.0f),
                glm::vec3(-GameConfig::BIG_FONT_SIZE,  0.0f, 1.0f),
                glm::vec3(-GameConfig::BIG_FONT_SIZE, -4 * GameConfig::BIG_FONT_SIZE, 1.0f),
                glm::vec3(-2 * GameConfig::BIG_FONT_SIZE, -3 * GameConfig::BIG_FONT_SIZE, 1.0f)
            },
            {
                glm::vec3( GameConfig::BIG_FONT_SIZE,  4 * GameConfig::BIG_FONT_SIZE, 1.0f),
                glm::vec3( 0.0f,  3 * GameConfig::BIG_FONT_SIZE, 1.0f),
                glm::vec3( 4 * GameConfig::BIG_FONT_SIZE,  3 * GameConfig::BIG_FONT_SIZE, 1.0f),
                glm::vec3( 3 * GameConfig::BIG_FONT_SIZE,  4 * GameConfig::BIG_FONT_SIZE, 1.0f)
            },
            {
                glm::vec3( 2 * GameConfig::BIG_FONT_SIZE,  4 * GameConfig::BIG_FONT_SIZE, 1.0f),
                glm::vec3( GameConfig::BIG_FONT_SIZE,  2 * GameConfig::BIG_FONT_SIZE, 1.0f),
                glm::vec3( 0.0f,  2 * GameConfig::BIG_FONT_SIZE, 1.0f),
                glm::vec3( 4 * GameConfig::BIG_FONT_SIZE,  2 * GameConfig::BIG_FONT_SIZE, 1.0f),
                glm::vec3( GameConfig::BIG_FONT_SIZE,  2 * GameConfig::BIG_FONT_SIZE, 1.0f),
                glm::vec3( 0.0f,  0.0f, 1.0f),
                glm::vec3( 0.0f, -2 * GameConfig::BIG_FONT_SIZE, 1.0f),
                glm::vec3( 0.0f,  0.0f, 1.0f),
                glm::vec3( 4 * GameConfig::BIG_FONT_SIZE,  0.0f, 1.0f),
                glm::vec3( 4 * GameConfig::BIG_FONT_SIZE, -GameConfig::BIG_FONT_SIZE, 1.0f),
                glm::vec3( 4 * GameConfig::BIG_FONT_SIZE,  0.0f, 1.0f),
                glm::vec3( 2 * GameConfig::BIG_FONT_SIZE,  3 * GameConfig::BIG_FONT_SIZE, 1.0f)
            },
            {
                glm::vec3( 0.0f, -GameConfig::BIG_FONT_SIZE, 1.0f),
                glm::vec3( 3 * GameConfig::BIG_FONT_SIZE, -GameConfig::BIG_FONT_SIZE, 1.0f),
                glm::vec3( 4 * GameConfig::BIG_FONT_SIZE, -3 * GameConfig::BIG_FONT_SIZE, 1.0f),
                glm::vec3( 3 * GameConfig::BIG_FONT_SIZE, -4 * GameConfig::BIG_FONT_SIZE, 1.0f)
            },
            {
                glm::vec3( 2 * GameConfig::BIG_FONT_SIZE,  GameConfig::BIG_FONT_SIZE, 1.0f),
                glm::vec3( GameConfig::BIG_FONT_SIZE, -4 * GameConfig::BIG_FONT_SIZE, 1.0f),
                glm::vec3( 0.0f, -3 * GameConfig::BIG_FONT_SIZE, 1.0f)
            }
        },
        std::vector<std::vector<Shape::RGBColor>>{
            std::vector<Shape::RGBColor>(4, static_cast<Shape::RGBColor>(glm::make_vec3(GameConfig::WIN_BG_COLOR))),
            std::vector<Shape::RGBColor>(12, static_cast<Shape::RGBColor>(glm::make_vec3(GameConfig::WIN_TEXT_COLOR))),
            std::vector<Shape::RGBColor>(4, static_cast<Shape::RGBColor>(glm::make_vec3(GameConfig::WIN_TEXT_COLOR))),
            std::vector<Shape::RGBColor>(12, static_cast<Shape::RGBColor>(glm::make_vec3(GameConfig::WIN_TEXT_COLOR))),
            std::vector<Shape::RGBColor>(4, static_cast<Shape::RGBColor>(glm::make_vec3(GameConfig::WIN_TEXT_COLOR))),
            std::vector<Shape::RGBColor>(3, static_cast<Shape::RGBColor>(glm::make_vec3(GameConfig::WIN_TEXT_COLOR)))
        },
        std::vector<unsigned int>{ GL_TRIANGLE_FAN, GL_LINE_STRIP, GL_LINE_STRIP, GL_LINE_STRIP, GL_LINE_STRIP, GL_LINE_STRIP }
    );
}

Shape::Shape<glm::vec3, Shape::RGBColor> getLoseVertices() {
    return Shape::Shape<glm::vec3, Shape::RGBColor>(
        std::vector<std::vector<glm::vec3>>{
            {
                glm::vec3(-6 * GameConfig::BIG_FONT_SIZE,  6 * GameConfig::BIG_FONT_SIZE, 0.5f),
                glm::vec3( 6 * GameConfig::BIG_FONT_SIZE,  6 * GameConfig::BIG_FONT_SIZE, 0.5f),
                glm::vec3( 6 * GameConfig::BIG_FONT_SIZE, -6 * GameConfig::BIG_FONT_SIZE, 0.5f),
                glm::vec3(-6 * GameConfig::BIG_FONT_SIZE, -6 * GameConfig::BIG_FONT_SIZE, 0.5f),

            },
            {
                glm::vec3(-4 * GameConfig::BIG_FONT_SIZE,  4 * GameConfig::BIG_FONT_SIZE, 1.0f),
                glm::vec3(-GameConfig::BIG_FONT_SIZE,  4 * GameConfig::BIG_FONT_SIZE, 1.0f),
                glm::vec3(-GameConfig::BIG_FONT_SIZE, -GameConfig::BIG_FONT_SIZE, 1.0f),
                glm::vec3(-4 * GameConfig::BIG_FONT_SIZE, -GameConfig::BIG_FONT_SIZE, 1.0f),
                glm::vec3(-4 * GameConfig::BIG_FONT_SIZE,  0.0f, 1.0f),
                glm::vec3(-GameConfig::BIG_FONT_SIZE,  0.0f, 1.0f),
                glm::vec3(-4 * GameConfig::BIG_FONT_SIZE,  0.0f, 1.0f),
                glm::vec3(-4 * GameConfig::BIG_FONT_SIZE,  GameConfig::BIG_FONT_SIZE, 1.0f),
                glm::vec3(-GameConfig::BIG_FONT_SIZE,  GameConfig::BIG_FONT_SIZE, 1.0f),
                glm::vec3(-4 * GameConfig::BIG_FONT_SIZE,  GameConfig::BIG_FONT_SIZE, 1.0f),
                glm::vec3(-4 * GameConfig::BIG_FONT_SIZE,  4 * GameConfig::BIG_FONT_SIZE, 1.0f)
            },
            {
                glm::vec3(-3 * GameConfig::BIG_FONT_SIZE, -2 * GameConfig::BIG_FONT_SIZE, 1.0f),
                glm::vec3(-4 * GameConfig::BIG_FONT_SIZE, -4 * GameConfig::BIG_FONT_SIZE, 1.0f)
            },
            {
                glm::vec3(-2 * GameConfig::BIG_FONT_SIZE, -2 * GameConfig::BIG_FONT_SIZE, 1.0f),
                glm::vec3(-GameConfig::BIG_FONT_SIZE, -4 * GameConfig::BIG_FONT_SIZE, 1.0f),
            },
            {
                glm::vec3( 0.0f,  0.0f, 1.0f),
                glm::vec3( 2 * GameConfig::BIG_FONT_SIZE,  4 * GameConfig::BIG_FONT_SIZE, 1.0f),
                glm::vec3( GameConfig::BIG_FONT_SIZE,  2 * GameConfig::BIG_FONT_SIZE, 1.0f),
                glm::vec3( 4 * GameConfig::BIG_FONT_SIZE,  2 * GameConfig::BIG_FONT_SIZE, 1.0f),
                glm::vec3( 2 * GameConfig::BIG_FONT_SIZE, -2 * GameConfig::BIG_FONT_SIZE, 1.0f),
                glm::vec3( GameConfig::BIG_FONT_SIZE,  GameConfig::BIG_FONT_SIZE, 1.0f),
                glm::vec3( 2 * GameConfig::BIG_FONT_SIZE, -2 * GameConfig::BIG_FONT_SIZE, 1.0f),
                glm::vec3( 0.0f, -4 * GameConfig::BIG_FONT_SIZE, 1.0f),
                glm::vec3( 2 * GameConfig::BIG_FONT_SIZE, -2 * GameConfig::BIG_FONT_SIZE, 1.0f),
                glm::vec3( 4 * GameConfig::BIG_FONT_SIZE, -4 * GameConfig::BIG_FONT_SIZE, 1.0f)
            }
        },
        std::vector<std::vector<Shape::RGBColor>>{
            std::vector<Shape::RGBColor>(4, static_cast<Shape::RGBColor>(glm::make_vec3(GameConfig::LOSE_BG_COLOR))),
            std::vector<Shape::RGBColor>(11, static_cast<Shape::RGBColor>(glm::make_vec3(GameConfig::LOSE_TEXT_COLOR))),
            std::vector<Shape::RGBColor>(2, static_cast<Shape::RGBColor>(glm::make_vec3(GameConfig::LOSE_TEXT_COLOR))),
            std::vector<Shape::RGBColor>(2, static_cast<Shape::RGBColor>(glm::make_vec3(GameConfig::LOSE_TEXT_COLOR))),
            std::vector<Shape::RGBColor>(10, static_cast<Shape::RGBColor>(glm::make_vec3(GameConfig::LOSE_TEXT_COLOR)))
        },
        std::vector<unsigned int>{ GL_TRIANGLE_FAN, GL_LINE_STRIP, GL_LINE_STRIP, GL_LINE_STRIP, GL_LINE_STRIP }
    );
}