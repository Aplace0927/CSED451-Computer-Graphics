#ifndef SCENEGRAPH_HPP
#define SCENEGRAPH_HPP

#include <vector>
#include <algorithm>
#include <glm/glm.hpp>
#include <GL/glew.h>

#include "utility.hpp"
#include "shape.hpp"

namespace Transform {
    template <typename T, typename C>
    class Transform {
        public:
            Transform(Shape::Shape<T, C> shape) : shape(shape), transformAnimateMatrix([](time_t) { return glm::mat4(1.0f); }), transformMatrix(glm::mat4(1.0f)) {}
            ~Transform<T, C>() {
                for (Transform<T, C>* child : children) {
                    delete child;
                }
            }

            /**
             * @fn draw
             * @param currentTime
             * 
             * @brief Draw the Shape with transformation matrix applied.
             * Recursively draws the child Transform nodes as well.
             * Since the transformation matrix is time-dependent (for animation), the matrix is passed as a function of time.
             */
            void _draw(time_t currentTime) {
                glPushMatrix(); // Save current matrix
                // Apply transformation matrix for current time
                glm::mat4 M = transformMatrix * transformAnimateMatrix(currentTime);
                glMultMatrixf(glm::value_ptr(M));
                shape.draw();
                // Recursively draw children
                for (Transform<T, C>* child : children) {
                    child->_draw(currentTime);
 				}
                glPopMatrix();
            }

            void draw(time_t currentTime) {
                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();
                _draw(currentTime);
            }

            /**
             * @brief Adding/Deleting/Accessing child Transform nodes.
             * If removing a child Transform node, it will delete the descendants as well.
             * 
             * @fn addChild
             * @fn removeChild
             * @fn getNthChild
             */
            void addChild(Transform<T, C>* child) {
                children.push_back(child);
            }
            void removeChild(Transform<T, C>* child) {
                children.erase(std::remove(children.begin(), children.end(), child), children.end());
            }
            Transform<T, C>* getNthChild(size_t n) const {
                if (n < children.size()) {
                    return children[n];
                }
                return nullptr;
            }
            size_t getChildCount() const {
                return children.size();
            }

            /**
             * @fn changeShape
             * @fn checkSubShapeEmpty
             * @fn popSubShape
             * @fn clearSubShapes
             * @fn addSubShape
             * 
             * Since Transform object is NOT storing the BoundingBox, changing the shape will NOT update the bounding box.
             * Use @fn Transform::getBoundingBox() to get the updated bounding box.
             */
            void changeShape(const Shape::Shape<T, C> &newShape) {
                shape = newShape;
            }

            bool checkSubShapeEmpty() const { return shape.checkSubShapeEmpty(); }

            void popSubShape() {
                shape.popSubShape();
            }

            void clearSubShapes() { shape.clearSubShapes(); }

            void addSubShape(const std::vector<T> &vertices, const std::vector<C> &colors,
                            unsigned int drawMethod) {
                shape.addSubShape(vertices, colors, drawMethod);
            }

            /**
             * @fn getBoundingBox
             * 
             * @brief Get the bounding box of the shape. Recursively merges the bounding boxes of child Transform nodes.
             * Since the transformation matrix is time-dependent (for animation), the matrix is applied to the bounding box as well.
             */
            BoundingBox::BoundingBox<T> getBoundingBox(time_t time) const {
                BoundingBox::BoundingBox<T> bbox = shape.getBoundingBox();
                for(Transform<T, C>* child : children) {
                    bbox = bbox | child->getBoundingBox(time);
                }

                // Apply transformation matrix to bounding box corners glm::vec3 min = bbox.start;
                glm::vec3 min = bbox.start;
                glm::vec3 max = bbox.end;

                std::array<glm::vec3, 8> corners = {
                    glm::vec3(min.x, min.y, min.z),
                    glm::vec3(max.x, min.y, min.z),
                    glm::vec3(min.x, max.y, min.z),
                    glm::vec3(max.x, max.y, min.z),
                    glm::vec3(min.x, min.y, max.z),
                    glm::vec3(max.x, min.y, max.z),
                    glm::vec3(min.x, max.y, max.z),
                    glm::vec3(max.x, max.y, max.z)
                };

                // Apply transformMatrix first - time-independent (user moving/rotating/scaling)
                // Then apply transformAnimateMatrix - time-dependent animation (animation moving/rotating/scaling)
                glm::mat4 M = transformMatrix * transformAnimateMatrix(time);

                for (auto& c : corners) {
                    c = glm::vec3(M * glm::vec4(c, 1.0f));
                }

                glm::vec3 newMin = corners[0];
                glm::vec3 newMax = corners[0];

                for (const auto& c : corners) {
                    newMin = glm::min(newMin, c);
                    newMax = glm::max(newMax, c);
                }

                return BoundingBox::BoundingBox<T>(newMin, newMax);
            }

            T getCenter() const {
                glm::mat4 M = transformMatrix * transformAnimateMatrix(Utility::getCurrentTimeMS());
                T thisCenter = M * glm::vec4(shape.getCenter(), 1.0f);
                for (Transform<T, C>* child : children) {
                    thisCenter += M * glm::vec4(child->getCenter(), 1.0f);
                }
                return thisCenter / static_cast<float>(children.size() + 1);
            }

            std::function<glm::mat4(time_t)> transformAnimateMatrix;
            glm::mat4 transformMatrix;

        private:
            Shape::Shape<T, C> shape;
            Transform<T, C>* parent;
            std::vector<Transform<T, C>*> children;
    };

    Transform<glm::vec3, Shape::RGBColor>* createPlayer();
    Transform<glm::vec3, Shape::RGBColor>* createEnemy();
    Transform<glm::vec3, Shape::RGBColor>* createBullet(Shape::RGBColor color);
} // namespace Transform
#endif // SCENEGRAPH_HPP
