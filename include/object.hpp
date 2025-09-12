#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "shape.hpp"
#include "boundingbox.hpp"

namespace Object {
    template <typename T, size_t D, typename C>
    class Object {
    public:
        Object(const Shape::Shape<T, D, C> &_shape): shape(_shape), boundingBox(_shape.getBoundingBox()) {}

        void update(const std::array<T, D>& displacement) {
            shape.update(displacement);
            boundingBox.update(displacement);
        }

        void draw() {
            shape.draw();
        }
    private:
        Shape::Shape<T, D, C> shape;
        BoundingBox::BoundingBox<T, D> boundingBox;
    };
}

#endif // OBJECT_HPP