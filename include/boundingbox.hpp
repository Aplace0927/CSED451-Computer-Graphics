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
            auto it_d = displacement.begin();
            auto it_s = start.begin();
            auto it_e = end.begin();
            for(
                ; it_d != displacement.end() && it_s != start.end() && it_e != end.end();
                ++it_d, ++it_s, ++it_e
            ) {
                *it_s += *it_d;
                *it_e += *it_d;
            }
        }
        
        bool operator&(
            const BoundingBox<T, D>& other
        ) const {
            typename std::array<T, D>::const_iterator it_s, it_e, it_o_s, it_o_e;
            for (
                it_s = start.begin(), it_e = end.begin(), it_o_s = other.start.begin(), it_o_e = other.end.begin();
                it_s != start.end() && it_e != end.end() && it_o_s != other.start.end() && it_o_e != other.end.end();
                ++it_s, ++it_e, ++it_o_s, ++it_o_e
            )
            {
                if (not (*it_e < *it_o_s || *it_s > *it_o_e)) {
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