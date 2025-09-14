#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <vector>
#include <array>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "boundingbox.hpp"
#include "config.hpp"


namespace Shape {
    typedef glm::vec3 RGBColor;
    typedef glm::vec4 RGBAColor;

    template <typename T, typename C>
    class Shape {
    public:
        Shape(
            const std::vector<std::vector<T>>& _subshapes,
            const std::vector<std::vector<C>>& _colors,
            const std::vector<unsigned int>& _drawMethod
        ): subshapes(_subshapes), colors(_colors), drawMethod(_drawMethod) {
            throw std::runtime_error("Shape constructor not implemented for this specialization");
        }

        T getCenter() const {
            return center;
        }

        virtual BoundingBox::BoundingBox<T> move(const T& displacement) {throw std::runtime_error("move() not implemented for this Shape specialization");};
        virtual BoundingBox::BoundingBox<T> rotate(
            const T& rotation,
            const T& pivot
        ) {throw std::runtime_error("rotate() not implemented for this Shape specialization");};

        virtual void draw() {throw std::runtime_error("draw() not implemented for this Shape specialization");};

    private:
        T center;
        std::vector<std::vector<T>> subshapes;
        std::vector<std::vector<C>> colors;
        std::vector<unsigned int> drawMethod;        

        BoundingBox::BoundingBox<T> getBoundingBox() const {
            throw std::runtime_error("getBoundingBox() not implemented for this Shape specialization");
        }
    };
}
#endif // SHAPE_HPP