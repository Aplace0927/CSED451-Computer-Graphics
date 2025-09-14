#ifndef BOUNDINGBOX_HPP
#define BOUNDINGBOX_HPP

#include <cstddef>
#include <array>
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace BoundingBox {
    template<typename T>
    class BoundingBox {
    public:
        // Default constructor
        BoundingBox() {
            throw std::runtime_error("Default constructor not implemented for this BoundingBox specialization");
        }

        BoundingBox(
            T& _start,
            T& _end
        ): start(_start), end(_end) {}
        
        // Boundingbox itself cannot updated: only via Shape's applyTransition

        // Copy constructor
        BoundingBox(const BoundingBox<T>& other)
            : start(other.start), end(other.end) {}

        // Move constructor
        BoundingBox(BoundingBox<T>&& other) noexcept
            : start(std::move(other.start)), end(std::move(other.end)) {}

        // Copy assignment operator
        BoundingBox<T>& operator=(const BoundingBox<T>& other) {
            if (this != &other) {
                start = other.start;
                end = other.end;
            }
            return *this;
        }

        bool operator&(
            const BoundingBox<T>& other
        ) const {
            throw std::runtime_error("Collision detection operator not implemented for this BoundingBox specialization");
        }

        void draw() {
            throw std::runtime_error("draw() not implemented for this BoundingBox specialization");
        }

    private:
        // Add bounding box state variables here
        T start;
        T end;
    };
}

#endif