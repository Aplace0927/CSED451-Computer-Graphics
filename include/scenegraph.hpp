#ifndef SCENEGRAPH_HPP
#define SCENEGRAPH_HPP

#include <vector>
#include <algorithm>
#include <glm/glm.hpp>

#include "shape.hpp"


namespace SceneGraph {
    template <typename T, typename C>
    class SceneGraph {
        public:
            SceneGraph(Shape::Shape<T, C> shape) : shape(shape), transformMatrix(glm::mat4(1.0f)) {}
            ~SceneGraph<T, C>() {
                for (SceneGraph<T, C>* child : children) {
                    delete child;
                }
            }

            /**
             * @fn draw
             * @param currentTime
             * 
             * @brief Draw the Shape with transformation matrix applied.
             * Recursively draws the child SceneGraph nodes as well.
             * Since the transformation matrix is time-dependent (for animation), the matrix is passed as a function of time.
             */
            void draw(time_t currentTime) {
                glPushMatrix(); // Save current matrix
                // Apply transformation matrix for current time
                glMultMatrix(glm::value_ptr(transformMatrix(currentTime)));
                shape.draw();
                // Recursively draw children
                for (SceneGraph<T, C>* child : children) {
                    child->draw(currentTime);
                }
                glPopMatrix();
            }

            /**
             * @brief Set/Get transform Matrix for animation.
             * As the matrix is time-dependent (for animation), the matrix is stored as a function.
             * 
             * @fn setTransform
             * @fn getTransform
             */

            void setTransform(const std::function<glm::mat4(time_t)>& matrix) {
                transformMatrix = matrix;
            }


            std::function<glm::mat4(time_t)> getTransform() const {
                return transformMatrix;
            }

            /**
             * @brief Adding/Deleting/Accessing child SceneGraph nodes.
             * If removing a child SceneGraph node, it will delete the descendants as well.
             * 
             * @fn addChild
             * @fn removeChild
             * @fn getNthChild
             */
            void addChild(SceneGraph<T, C>* child) {
                children.push_back(child);
                child->parent = this;
            }
            void removeChild(SceneGraph<T, C>* child) {
                children.erase(std::remove(children.begin(), children.end(), child), children.end());
            }
            SceneGraph<T, C>* getNthChild(size_t n) const {
                if (n < children.size()) {
                    return children[n];
                }
                return nullptr;
            }

            /**
             * @fn changeShape
             * @fn checkSubShapeEmpty
             * @fn popSubShape
             * @fn clearSubShapes
             * @fn addSubShape
             * 
             * Since sceneGraph object is NOT storing the BoundingBox, changing the shape will NOT update the bounding box.
             * Use @fn SceneGraph::getBoundingBox() to get the updated bounding box.
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
             * @brief Get the bounding box of the shape. Recursively merges the bounding boxes of child SceneGraph nodes.
             * Since the transformation matrix is time-dependent (for animation), the matrix is applied to the bounding box as well.
             */
            BoundingBox::BoundingBox<T> getBoundingBox(time_t time) const {
                BoundingBox::BoundingBox<T> bbox = shape.getBoundingBox();
                for(SceneGraph<T, C>* child : children) {
                    bbox = bbox | child->getBoundingBox();
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

                glm::mat4 M = transformMatrix(time);

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

        private:
            Shape::Shape<T, C> shape;
            std::function<glm::mat4(time_t)> transformMatrix;
            
            std::vector<SceneGraph<T, C>*> children;
    };
} // namespace SceneGraph

#endif // SCENEGRAPH_HPP
