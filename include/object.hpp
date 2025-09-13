#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "shape.hpp"
#include "boundingbox.hpp"

namespace Object {
    template <typename T, size_t D, typename C>
    class Object {
    public:
        Object(
            const std::array<T, D>& _position,
            const Shape::Shape<T, D, C> &_shape
        ): shape(_shape) {
            // Update to actual position (also initializes bounding box) 
            boundingBox = shape.move(_position);
        }

        void move(const std::array<T, D>& displacement) {
            boundingBox = shape.move(displacement);
        }

        void rotate(const std::array<T, D>& angles, const std::array<T, D>& pivot) {
            boundingBox = shape.rotate(angles, pivot);
        }
        void applyTransition(const glm::mat<D+1, D+1, T>& transition) {
            boundingBox = shape.applyTransition(transition);
        }

        std::array<T, D> getCenter() const {
            return shape.getCenter();
        }
        
        void draw() {
            shape.draw();
            #ifdef BOUNDING_BOX_DEBUG
            boundingBox.draw();
            #endif
        }
        
    private:
        Shape::Shape<T, D, C> shape;
        BoundingBox::BoundingBox<T, D> boundingBox;
    };
}

#endif // OBJECT_HPP