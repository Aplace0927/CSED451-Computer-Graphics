#include "transform.hpp"

namespace Transform {
    Transform<glm::vec3, Shape::RGBColor>* createPlayer() {
        Shape::Shape<glm::vec3, Shape::RGBColor> playerShape(
            std::vector<std::vector<glm::vec3>>{
                {glm::vec3(0.0f, 17.3f, 0.0f),
                glm::vec3(-17.3f, -10.0f, 0.0f),
                glm::vec3(17.3f, -10.0f, 0.0f)}
            },
            std::vector<std::vector<Shape::RGBColor>>{
                {Shape::RGBColor(1.0f, 1.0f, 0.0f),
                Shape::RGBColor(0.0f, 1.0f, 1.0f),
                Shape::RGBColor(1.0f, 0.0f, 1.0f)}
            },
            // drawMethod: vector of draw methods for each subshape
            std::vector<unsigned int>{GL_TRIANGLES}
        );
        Transform<glm::vec3, Shape::RGBColor>* playerTransform = new Transform<glm::vec3, Shape::RGBColor>(playerShape);
        playerTransform->transformMatrix = glm::translate(
            glm::identity<glm::mat4>(),
            glm::vec3(0.0f, -GameConfig::WINDOW_HEIGHT / 4, 0.0f)
        );
        playerTransform->transformAnimateMatrix = [](time_t) { return glm::identity<glm::mat4>(); };
        return playerTransform;
    }

    Transform<glm::vec3, Shape::RGBColor>* createEnemy() {
        Shape::Shape<glm::vec3, Shape::RGBColor> enemyShape(
            std::vector<std::vector<glm::vec3>>{{
                glm::vec3(-40.0f, 0.0f, 0.0f),
                glm::vec3(-20.0f, 34.6f, 0.0f),
                glm::vec3(20.0f, 34.6f, 0.0f),
                glm::vec3(40.0f, 0.0f, 0.0f),
                glm::vec3(20.0f, -34.6f, 0.0f),
                glm::vec3(-20.0f, -34.6f, 0.0f),
                glm::vec3(-40.0f, 0.0f, 0.0f),
            }},
            std::vector<std::vector<Shape::RGBColor>>{{
                Shape::RGBColor(1.0f, 0.0f, 0.0f),
                Shape::RGBColor(1.0f, 0.0f, 0.0f),
                Shape::RGBColor(1.0f, 0.0f, 0.0f),
                Shape::RGBColor(1.0f, 0.0f, 0.0f),
                Shape::RGBColor(1.0f, 0.0f, 0.0f),
                Shape::RGBColor(1.0f, 0.0f, 0.0f),
                Shape::RGBColor(1.0f, 0.0f, 0.0f),
            }},
            std::vector<unsigned int>{GL_TRIANGLE_FAN}
        );
        Transform<glm::vec3, Shape::RGBColor>* enemyTransform = new Transform<glm::vec3, Shape::RGBColor>(enemyShape);
        enemyTransform->transformMatrix = glm::translate(
            glm::identity<glm::mat4>(),
            glm::vec3(0.0f, GameConfig::WINDOW_HEIGHT / 4, 0.0f)
        );
        
        enemyTransform->transformAnimateMatrix = [](time_t time) { return glm::identity<glm::mat4>(); };

        Shape::Shape<glm::vec3, Shape::RGBColor> enemyLeg(
            std::vector<std::vector<glm::vec3>>{{
                glm::vec3(-60.0f, -5.0f, 0.0f),
                glm::vec3(60.0f, -5.0f, 0.0f),
                glm::vec3(60.0f, 5.0f, 0.0f),
                glm::vec3(-60.0f, 5.0f, 0.0f),
                glm::vec3(-60.0f, -5.0f, 0.0f),
            }},
            std::vector<std::vector<Shape::RGBColor>> {{
                Shape::RGBColor(0.0f, 0.0f, 1.0f),
                Shape::RGBColor(0.0f, 0.0f, 1.0f),
                Shape::RGBColor(0.0f, 0.0f, 1.0f),
                Shape::RGBColor(0.0f, 0.0f, 1.0f),
                Shape::RGBColor(0.0f, 0.0f, 1.0f),
            }},
            std::vector<unsigned int>{GL_TRIANGLE_FAN}
        );

        Transform<glm::vec3, Shape::RGBColor>* enemyLegTransform_1 = new Transform<glm::vec3, Shape::RGBColor>(enemyLeg);
        enemyLegTransform_1->transformMatrix = glm::translate(
            glm::identity<glm::mat4>(),
            glm::vec3(20.0f, 0.0f, 0.2f)
        );
        enemyLegTransform_1->transformAnimateMatrix = [](time_t time) {
            return glm::translate(
                glm::identity<glm::mat4>(),
                glm::vec3(glm::cos(time), glm::sin(time), 0.0f)
            );
        };

        Transform<glm::vec3, Shape::RGBColor>* enemyLegTransform_2 = new Transform<glm::vec3, Shape::RGBColor>(enemyLeg);
        enemyLegTransform_2->transformMatrix = glm::rotate(
            glm::identity<glm::mat4>(),
            glm::radians(120.0f),
            glm::vec3(0.0f, 0.0f, 1.0f)
        ) * glm::translate(
            glm::identity<glm::mat4>(),
            glm::vec3(0.0f, 20.0f, 0.2f)
        );
        enemyLegTransform_2->transformAnimateMatrix = [](time_t time) {
            return glm::translate(
                glm::identity<glm::mat4>(),
                glm::vec3(glm::cos(time), glm::sin(time), 0.0f)
            );
        };

        
        enemyTransform->addChild(enemyLegTransform_1);
        enemyTransform->addChild(enemyLegTransform_2);

        Shape::Shape<glm::vec3, Shape::RGBColor> enemyEye(
            std::vector<std::vector<glm::vec3>>{{
                glm::vec3(-10.0f, 10.0f, 0.0f),
                glm::vec3(10.0f, 10.0f, 0.0f),
                glm::vec3(10.0f, -10.0f, 0.0f),
                glm::vec3(-10.0f, -10.0f, 0.0f),
                glm::vec3(-10.0f, 10.0f, 0.0f),
            }},
            std::vector<std::vector<Shape::RGBColor>> {{
                Shape::RGBColor(1.0f, 1.0f, 1.0f),
                Shape::RGBColor(1.0f, 1.0f, 1.0f),
                Shape::RGBColor(1.0f, 1.0f, 1.0f),
                Shape::RGBColor(1.0f, 1.0f, 1.0f),
                Shape::RGBColor(1.0f, 1.0f, 1.0f),
            }},
            std::vector<unsigned int>{GL_TRIANGLE_FAN}
        );
        Transform<glm::vec3, Shape::RGBColor>* enemyEyeTransform_1 = new Transform<glm::vec3, Shape::RGBColor>(enemyEye);
        enemyEyeTransform_1->transformMatrix = glm::identity<glm::mat4>();
        enemyEyeTransform_1->transformAnimateMatrix = [](time_t) { return glm::identity<glm::mat4>(); };

        enemyLegTransform_1->addChild(enemyEyeTransform_1);
        return enemyTransform;
    }

    Transform<glm::vec3, Shape::RGBColor>* createBullet(Shape::RGBColor color) {
        Shape::Shape<glm::vec3, Shape::RGBColor> bulletShape(
            std::vector<std::vector<glm::vec3>>{{
                glm::vec3(-2.0f, 2.0f, 0.0f),
                glm::vec3(2.0f, 2.0f, 0.0f),
                glm::vec3(2.0f, -2.0f, 0.0f),
                glm::vec3(-2.0f, -2.0f, 0.0f),
                glm::vec3(-2.0f, 2.0f, 0.0f),
            }},
            std::vector<std::vector<Shape::RGBColor>>{
                {color, color, color, color, color}},
            std::vector<unsigned int>{GL_TRIANGLE_FAN}
        );
        Transform<glm::vec3, Shape::RGBColor>* bulletTransform = new Transform<glm::vec3, Shape::RGBColor>(bulletShape);
        bulletTransform->transformMatrix = glm::translate(
            glm::identity<glm::mat4>(),
            glm::vec3(0.0f, 0.0f, 0.0f)
        );
        bulletTransform->transformAnimateMatrix = [](time_t time) { return glm::identity<glm::mat4>(); };
        return bulletTransform;
    }
}