#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "shape.hpp"
#include "boundingbox.hpp"

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
        
    private:
        Shape::Shape<T, C> shape;
        BoundingBox::BoundingBox<T> boundingBox;
    };
}

#endif // OBJECT_HPP