#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "shape.hpp"
#include "boundingbox.hpp"
#include "graphicsmanager.hpp"
#include "physicsmanager.hpp"

namespace Object {
    template <typename T, typename C>
    class Object {
    public:
        Object(
            const T  &_position,
            const Shape::Shape<T, C> &_shape
        ): shape(_shape) {
            // Update to actual position (also initializes bounding box) 
            boundingBox = shape.move(_position);
            update_ptr = GraphicsManager::GraphicsManager::getInstance().registerHandler([this]() {this->update();});
            fixedUpdate_ptr = PhysicsManager::PhysicsManager::getInstance().registerHandler([this]() {this->fixedUpdate();});
        }

        void move(const T& displacement) {
            boundingBox = shape.move(displacement);
        }

        void rotate(const T& angles, const T& pivot) {
            boundingBox = shape.rotate(angles, pivot);
        }
        void applyTransition(const glm::mat4& transition) {
            boundingBox = shape.applyTransition(transition);
        }

        T getCenter() const {
            return shape.getCenter();
        }
        
        void draw() {
            shape.draw();
            #ifdef BOUNDING_BOX_DEBUG
            boundingBox.draw();
            #endif
        }
        
        void update() {}
        void fixedUpdate() {}

    private:
        Shape::Shape<T, C> shape;
        BoundingBox::BoundingBox<T> boundingBox;
        std::shared_ptr<std::function<void()>> update_ptr;
        std::shared_ptr<std::function<void()>> fixedUpdate_ptr;
    };
}

#endif // OBJECT_HPP