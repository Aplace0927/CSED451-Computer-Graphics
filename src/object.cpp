#include "object.hpp"

// template <typename T, size_t D, typename C>
// Object::Object<T, D, C>::Object(const Shape::Shape<T, D, C> &_shape) : shape(_shape) {
//     // Find min and max point from the shapes
//     std::array<T, D> minPoint, maxPoint;
//     minPoint.fill(std::numeric_limits<T>::max());
//     maxPoint.fill(std::numeric_limits<T>::min());

//     for (auto subshape: _shape.subshapes) {
//         for (auto vertex: subshape) {
//             for (size_t i = 0; i < D; ++i) {
//                 if (vertex[i] < minPoint[i]) minPoint[i] = vertex[i];
//                 if (vertex[i] > maxPoint[i]) maxPoint[i] = vertex[i];
//             }
//         }
//     }
//     boundingBox = BoundingBox::BoundingBox<T, D>(minPoint, maxPoint);
// }

// template <typename T, size_t D, typename C>
// void Object::Object<T, D, C>::update(
//     const std::array<T, D>& displacement
// ) {
//     shape.update(displacement);
//     boundingBox.update(displacement);
// }

// template <typename T, size_t D, typename C>
// void Object::Object<T, D, C>::draw() {
//     shape.draw();
// }