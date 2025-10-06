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