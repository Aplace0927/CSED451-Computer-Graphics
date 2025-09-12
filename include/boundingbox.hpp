#ifndef BOUNDINGBOX_HPP
#define BOUNDINGBOX_HPP

#include <cstddef>
#include <array>

namespace BoundingBox {
    template<typename T, size_t D>
    class BoundingBox {
    public:
        BoundingBox(const std::array<T, D>& _start, const std::array<T, D>& _end): start(_start), end(_end) {}

        void update(
            const std::array<T, D>& displacement
        ) {
            for (size_t i = 0; i < D; ++i) {
                start[i] += displacement[i];
                end[i] += displacement[i];
            }
        }
        
        bool operator&(
            const BoundingBox<T, D>& other
        ) const {
            for (size_t i = 0; i < D; ++i) {
                if (not (end[i] < other.start[i] || start[i] > other.end[i])) {
                    return true;    // Collides in dim i
                }
            }
            return false;   // No collision in any dimension
        }
    private:
        // Add bounding box state variables here
        std::array<T, D> start;
        std::array<T, D> end;
    };
}

#endif