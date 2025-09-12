#include "shape.hpp"

// template <typename T, size_t D, typename C>
// Shape::Shape<T, D, C>::Shape(
//     const std::vector<std::vector<std::array<T, D>>>& _subshapes,
//     const std::vector<std::vector<C>>& _colors,
//     const std::vector<unsigned int>& _drawMethod
// ) : subshapes(_subshapes), colors(_colors), drawMethod(_drawMethod) {
//     //!TODO: Update future properties if necessary.
// }

// template <typename T, size_t D, typename C>
// void Shape::Shape<T, D, C>::update(const std::array<T, D>& displacement) {
//     for (auto& subshape : subshapes) {          // for each subshape:
//         for (auto& vertex : subshape) {         // for each vertex in the subshape:
//             for (size_t i = 0; i < D; ++i) {    // for each dimension:
//                 vertex[i] += displacement[i];   // update the vertex position
//             }
//         }
//     }
// }

// template<>
// void Shape::Shape<float, 3, Shape::RGBColor>::draw() {
//     for (size_t subShapeIdx = 0; subShapeIdx < subshapes.size(); ++subShapeIdx) {
//         glBegin(drawMethod[subShapeIdx]);
//         for (size_t subVertexIdx = 0; subVertexIdx < subshapes[subShapeIdx].size(); ++subVertexIdx) {
//             glColor3fv(colors[subShapeIdx][subVertexIdx].data());
//             glVertex3fv(subshapes[subShapeIdx][subVertexIdx].data());
//         }
//         glEnd();
//     }
// }
