#include "scenegraph.hpp"

namespace SceneGraph {
    SceneGraph<glm::vec3, Shape::RGBColor>* createPlayer() {
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
        SceneGraph<glm::vec3, Shape::RGBColor>* playerSceneGraph = new SceneGraph<glm::vec3, Shape::RGBColor>(playerShape);
        playerSceneGraph->transformMatrix = glm::translate(
            glm::identity<glm::mat4>(),
            glm::vec3(0.0f, -GameConfig::WINDOW_HEIGHT / 4, 0.0f)
        );
        playerSceneGraph->transformAnimateMatrix = [](time_t) { return glm::identity<glm::mat4>(); };
        return playerSceneGraph;
    }

    SceneGraph<glm::vec3, Shape::RGBColor>* createEnemy() {
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
        SceneGraph<glm::vec3, Shape::RGBColor>* enemySceneGraph = new SceneGraph<glm::vec3, Shape::RGBColor>(enemyShape);
        enemySceneGraph->transformMatrix = glm::translate(
            glm::identity<glm::mat4>(),
            glm::vec3(0.0f, GameConfig::WINDOW_HEIGHT / 4, 0.0f)
        );
        
        enemySceneGraph->transformAnimateMatrix = [](time_t time) { return glm::identity<glm::mat4>(); };

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

        SceneGraph<glm::vec3, Shape::RGBColor>* enemyLegSceneGraph_1 = new SceneGraph<glm::vec3, Shape::RGBColor>(enemyLeg);
        enemyLegSceneGraph_1->transformMatrix = glm::translate(
            glm::identity<glm::mat4>(),
            glm::vec3(20.0f, 0.0f, 0.2f)
        );
        enemyLegSceneGraph_1->transformAnimateMatrix = [](time_t time) {
            return glm::translate(
                glm::identity<glm::mat4>(),
                glm::vec3(glm::cos(time), glm::sin(time), 0.0f)
            );
        };

        SceneGraph<glm::vec3, Shape::RGBColor>* enemyLegSceneGraph_2 = new SceneGraph<glm::vec3, Shape::RGBColor>(enemyLeg);
        enemyLegSceneGraph_2->transformMatrix = glm::rotate(
            glm::identity<glm::mat4>(),
            glm::radians(120.0f),
            glm::vec3(0.0f, 0.0f, 1.0f)
        ) * glm::translate(
            glm::identity<glm::mat4>(),
            glm::vec3(0.0f, 20.0f, 0.2f)
        );
        enemyLegSceneGraph_2->transformAnimateMatrix = [](time_t time) {
            return glm::translate(
                glm::identity<glm::mat4>(),
                glm::vec3(glm::cos(time), glm::sin(time), 0.0f)
            );
        };

        
        enemySceneGraph->addChild(enemyLegSceneGraph_1);
        enemySceneGraph->addChild(enemyLegSceneGraph_2);

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
        SceneGraph<glm::vec3, Shape::RGBColor>* enemyEyeSceneGraph_1 = new SceneGraph<glm::vec3, Shape::RGBColor>(enemyEye);
        enemyEyeSceneGraph_1->transformMatrix = glm::identity<glm::mat4>();
        enemyEyeSceneGraph_1->transformAnimateMatrix = [](time_t) { return glm::identity<glm::mat4>(); };

        enemyLegSceneGraph_1->addChild(enemyEyeSceneGraph_1);
        return enemySceneGraph;
    }

    SceneGraph<glm::vec3, Shape::RGBColor>* createBullet(Shape::RGBColor color) {
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
        SceneGraph<glm::vec3, Shape::RGBColor>* bulletSceneGraph = new SceneGraph<glm::vec3, Shape::RGBColor>(bulletShape);
        bulletSceneGraph->transformMatrix = glm::translate(
            glm::identity<glm::mat4>(),
            glm::vec3(0.0f, 0.0f, 0.0f)
        );
        bulletSceneGraph->transformAnimateMatrix = [](time_t time) { return glm::identity<glm::mat4>(); };
        return bulletSceneGraph;
    }
}