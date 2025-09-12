#include "boundingbox.hpp"

// template<typename T, size_t D>
// BoundingBox::BoundingBox<T, D>::BoundingBox(
//     const std::array<T, D>& _start,
//     const std::array<T, D>& _end
// ): start(_start), end(_end) {
//     //!TODO: Update future properties if necessary.
// }

// template<typename T, size_t D>
// void BoundingBox::BoundingBox<T, D>::update(
//     const std::array<T, D>& displacement
// ) {
//     for (size_t i = 0; i < D; ++i) {
//         start[i] += displacement[i];
//         end[i] += displacement[i];
//     }
// }

// template<typename T, size_t D>
// bool BoundingBox::BoundingBox<T, D>::operator&(
//     const BoundingBox<T, D>& other
// ) const {
//     for (size_t i = 0; i < D; ++i) {
//         if (not (end[i] < other.start[i] || start[i] > other.end[i])) {
//             return true;    // Collides in dim i
//         }
//     }
//     return false;   // No collision in any dimension
// }
