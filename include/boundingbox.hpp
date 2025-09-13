#ifndef BOUNDINGBOX_HPP
#define BOUNDINGBOX_HPP

#include <cstddef>
#include <array>
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace BoundingBox {
    template<typename T, size_t D>
    class BoundingBox {
    public:
        // Default constructor
        BoundingBox() {
            start.fill(std::numeric_limits<T>::max());
            end.fill(std::numeric_limits<T>::min());
        }

        BoundingBox(
            const std::array<T, D>& _start,
            const std::array<T, D>& _end
        ): start(_start), end(_end) {}
        
        // Boundingbox itself cannot updated: only via Shape's applyTransition

        // Copy constructor
        BoundingBox(const BoundingBox<T, D>& other)
            : start(other.start), end(other.end) {}

        // Move constructor
        BoundingBox(BoundingBox<T, D>&& other) noexcept
            : start(std::move(other.start)), end(std::move(other.end)) {}

        // Copy assignment operator
        BoundingBox<T, D>& operator=(const BoundingBox<T, D>& other) {
            if (this != &other) {
                start = other.start;
                end = other.end;
            }
            return *this;
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

        void draw() {
            glBegin(GL_LINE_LOOP);
            glColor3f(1.0f, 0.0f, 0.0f); // Red color for bounding box
            glVertex3f(start[0], start[1], start[2]);
            glVertex3f(end[0], start[1], start[2]);
            glVertex3f(end[0], end[1], start[2]);
            glVertex3f(start[0], end[1], start[2]);
            glVertex3f(start[0], start[1], end[2]);
            glVertex3f(end[0], start[1], end[2]);
            glVertex3f(end[0], end[1], end[2]);
            glVertex3f(start[0], end[1], end[2]);
            glEnd();
        }

    private:
        // Add bounding box state variables here
        std::array<T, D> start;
        std::array<T, D> end;
    };

}

#endif