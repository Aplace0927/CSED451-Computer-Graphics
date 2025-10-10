#include "transform.hpp"
#include "healthbar.hpp"

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


        std::vector<glm::vec3> orbitPoints;
        for (int i = 0; i < 72; i++) {
            float angle = glm::radians(i * 5.0f); // 5
            orbitPoints.push_back(glm::vec3(30.0f * glm::cos(angle), 30.0f * glm::sin(angle), 0.0f));
        }
        std::vector<Shape::RGBColor> orbitColors;
        for (int i = 0; i < 72; i++) {
            float v;
            if (i > 36) {
                v = (72 - i) / 36.0f;
            }
            else {
                v = i / 36.0f;
            }
            orbitColors.push_back(Shape::RGBColor(0.0f, v, 1.0f - v));
        }
        Shape::Shape<glm::vec3, Shape::RGBColor> playerHealthOrbit(
            std::vector<std::vector<glm::vec3>>{orbitPoints},
            std::vector<std::vector<Shape::RGBColor>>{orbitColors},
            std::vector<unsigned int>{GL_LINE_LOOP}
        );

        Transform<glm::vec3, Shape::RGBColor>* playerHealthOrbitTransform = new Transform<glm::vec3, Shape::RGBColor>(playerHealthOrbit);
        playerHealthOrbitTransform->hasBoundingBox = false; // Orbit line does not contribute to bounding box
        playerHealthOrbitTransform->transformMatrix = glm::identity<glm::mat4>();
        playerHealthOrbitTransform->transformAnimateMatrix = [](time_t time) {
            return glm::rotate(
                glm::identity<glm::mat4>(),
                glm::radians(
                    Utility::getPhaseGenerator<float>(GameConfig::PLAYER_HEALTH_ORBIT_ROTATION_SPEED, 0.0f)
                ), // Rotate at 0.1 degree per millisecond
                glm::vec3(0.0f, 0.0f, 1.0f)
            );
        };

        const float gemSize = 3.0f;
        Shape::Shape<glm::vec3, Shape::RGBColor> playerHealthGem(
            std::vector<std::vector<glm::vec3>> {{
                    glm::vec3(-gemSize, gemSize, 0.0f),
                    glm::vec3( gemSize, gemSize, 0.0f),
                    glm::vec3( gemSize,-gemSize, 0.0f),
                    glm::vec3(-gemSize,-gemSize, 0.0f),
                    glm::vec3(-gemSize, gemSize, 0.0f)
            }},
            std::vector<std::vector<Shape::RGBColor>>{{
                Shape::RGBColor(0.0f, 0.0f, 1.0f),
                Shape::RGBColor(0.0f, 0.5f, 0.5f),
                Shape::RGBColor(0.0f, 1.0f, 0.0f),
                Shape::RGBColor(0.0f, 0.5f, 0.5f),
                Shape::RGBColor(0.0f, 0.0f, 1.0f)
            }},
            std::vector<unsigned int>{GL_TRIANGLE_FAN}
        );

        for(int i = 0; i < GameConfig::PLAYER_LIFE; i++) {
            Transform<glm::vec3, Shape::RGBColor>* playerHealthGemTransform = new Transform<glm::vec3, Shape::RGBColor>(playerHealthGem);
            playerHealthGemTransform->hasBoundingBox = false; // Health gem does not contribute to bounding box
            playerHealthGemTransform->transformMatrix = glm::translate(
                glm::identity<glm::mat4>(),
                glm::vec3(
                    30.0f * cos(glm::radians((360.0f / GameConfig::PLAYER_LIFE) * i)),
                    30.0f * sin(glm::radians((360.0f / GameConfig::PLAYER_LIFE) * i)),
                    0.2f
                )
            );
            playerHealthGemTransform->transformAnimateMatrix = [](time_t time){
                return glm::identity<glm::mat4>();
            };
            playerHealthOrbitTransform->addChild(playerHealthGemTransform);
        }
        playerTransform->addChild(playerHealthOrbitTransform);
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

        Transform<glm::vec3, Shape::RGBColor>* healthBarTransform = new Transform<glm::vec3, Shape::RGBColor>(
            HealthBar::HealthBar(
                glm::vec3(-30.0f, 60.0f, 0.0f), // digit position
                10.0f, // digit size
                glm::vec3(-40.0f, 40.0f, 0.0f), // gauge position
                80.0f, // gauge width
                10.0f, // gauge height
                GameConfig::ENEMY_LIFE // max health
            )
        );
        healthBarTransform->hasBoundingBox = false; // Health bar does not contribute to bounding box
        healthBarTransform->transformMatrix = glm::identity<glm::mat4>();
        healthBarTransform->transformAnimateMatrix = [](time_t time) { return glm::identity<glm::mat4>(); };
        enemyTransform->addChild(healthBarTransform);

        const float legLength = 25.0f;
        const float legSwingAngle = 30.0f;
        Shape::Shape<glm::vec3, Shape::RGBColor> enemyLeg(
            std::vector<std::vector<glm::vec3>>{{
                glm::vec3(0.0f, -5.0f, 0.0f),
                glm::vec3(legLength, -5.0f, 0.0f),
                glm::vec3(legLength, 5.0f, 0.0f),
                glm::vec3(0.0f, 5.0f, 0.0f),
                glm::vec3(0.0f, -5.0f, 0.0f),
            }},
            std::vector<std::vector<Shape::RGBColor>> {{
                Shape::RGBColor(1.0f, 0.0f, 0.0f),
                Shape::RGBColor(0.3f, 0.0f, 0.0f),
                Shape::RGBColor(0.3f, 0.0f, 0.0f),
                Shape::RGBColor(1.0f, 0.0f, 0.0f),
                Shape::RGBColor(1.0f, 0.0f, 0.0f),
            }},
            std::vector<unsigned int>{GL_TRIANGLE_FAN}
        );

        double legAngle[4] = {30.0, 150.0, 210.0, 330.0};
        for (double d: legAngle) {
            Transform<glm::vec3, Shape::RGBColor>* enemyLegTransformUpper = new Transform<glm::vec3, Shape::RGBColor>(enemyLeg);
            enemyLegTransformUpper->transformMatrix = glm::translate(
                glm::identity<glm::mat4>(),
                glm::vec3(
                    cos(glm::radians(d)) * legLength,
                    sin(glm::radians(d)) * legLength,
                    0.2f
                )
            );

            Transform<glm::vec3, Shape::RGBColor>* enemyLegTransformLower = new Transform<glm::vec3, Shape::RGBColor>(enemyLeg);
            enemyLegTransformLower->transformMatrix = glm::translate(
                glm::identity<glm::mat4>(),
                glm::vec3(
                    legLength,
                    0.0f,
                    0.2f
                )
            );

            if (90.0f < d && d < 270.0f) {
                enemyLegTransformUpper->transformAnimateMatrix = [legSwingAngle](time_t time) {
                    return glm::rotate(
                        glm::identity<glm::mat4>(),
                        glm::radians(180.0f - Utility::getPhaseOscillator<float>(-legSwingAngle, legSwingAngle, 0.2f)),
                        glm::vec3(0.0f, 0.0f, 1.0f)
                    );
                };
                enemyLegTransformLower->transformAnimateMatrix = [legSwingAngle](time_t time) {
                    return glm::rotate(
                        glm::identity<glm::mat4>(),
                        glm::radians(180.0f - Utility::getPhaseOscillator<float>(-legSwingAngle, legSwingAngle, 0.3f)),
                        glm::vec3(0.0f, 0.0f, 1.0f)
                    );
                };
            }
            else {
                enemyLegTransformUpper->transformAnimateMatrix = [legSwingAngle](time_t time) {
                return glm::rotate(
                    glm::identity<glm::mat4>(),
                    glm::radians(Utility::getPhaseOscillator<float>(-legSwingAngle, legSwingAngle, 0.2f)),
                    glm::vec3(0.0f, 0.0f, 1.0f)
                );
            };
                enemyLegTransformLower->transformAnimateMatrix = [legSwingAngle](time_t time) {
                    return glm::rotate(
                        glm::identity<glm::mat4>(),
                        glm::radians(-180.0f + Utility::getPhaseOscillator<float>(-legSwingAngle, legSwingAngle, 0.3f)),
                        glm::vec3(0.0f, 0.0f, 1.0f)
                    );
                };
            }

            enemyTransform->addChild(enemyLegTransformUpper);
            enemyLegTransformUpper->addChild(enemyLegTransformLower);
        }
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