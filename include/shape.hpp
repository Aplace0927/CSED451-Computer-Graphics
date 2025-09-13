#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <vector>
#include <array>
#include <GL/glew.h>

#include "boundingbox.hpp"
#include "config.hpp"


namespace Shape {
    typedef std::array<GLfloat, 3> RGBColor;
    typedef std::array<GLfloat, 4> RGBAColor;

    template <typename T, size_t D, typename C>
    class Shape {
    public:
        Shape(
            const std::vector<std::vector<std::array<T, D>>>& _subshapes,
            const std::vector<std::vector<C>>& _colors,
            const std::vector<unsigned int>& _drawMethod
        ): subshapes(_subshapes), colors(_colors), drawMethod(_drawMethod) {

        }

        void update(const std::array<T, D>& displacement) {
            typename std::array<T, D>::iterator it_v;
            typename std::array<T, D>::const_iterator it_d;
            for (auto& subshape : subshapes) {
                for (auto& vertex : subshape) {
                    for (
                        it_v = vertex.begin(), it_d = displacement.begin();
                        it_v != vertex.end() && it_d != displacement.end();
                        ++it_v, ++it_d
                    ) {
                        *it_v += *it_d;
                    }
                }
            }
        }

        BoundingBox::BoundingBox<T, D> getBoundingBox() const {
            // Compute and return the bounding box based on subshapes
            typename std::array<T, D>::iterator it_min, it_max;
            typename std::array<T, D>::const_iterator it_v;
            
            std::array<T, D> minPoint, maxPoint;
            minPoint.fill(std::numeric_limits<T>::max());
            maxPoint.fill(std::numeric_limits<T>::min());
            
            for (const auto& subshape : subshapes) {
                for (const auto& vertex : subshape) {
                    for (
                        it_v = vertex.begin(), it_min = minPoint.begin(), it_max = maxPoint.begin();
                        it_v != vertex.end() && it_min != minPoint.end() && it_max != maxPoint.end();
                        ++it_v, ++it_min, ++it_max
                    ) {
                        *it_min = std::min(*it_min, *it_v);
                        *it_max = std::max(*it_max, *it_v);
                    }
                }
            }
            return BoundingBox::BoundingBox<T, D>(minPoint, maxPoint);
        }

        virtual void draw() {
            // Default implementation (can be empty or generic)
        }

    private:
        std::vector<std::vector<std::array<T, D>>> subshapes;
        std::vector<std::vector<C>> colors;
        std::vector<unsigned int> drawMethod;        
    };

    // Explicit specialization for Shape<float, 3, RGBColor>
    template <>
    inline void Shape<float, 3, RGBColor>::draw() {
        auto it_d = drawMethod.begin();
        auto it_shape = subshapes.begin();
        auto it_color = colors.begin();
        for (
            ; it_d != drawMethod.end() && it_shape != subshapes.end() && it_color != colors.end();
            ++it_d, ++it_shape, ++it_color
        ) {
            glBegin(*it_d);
            for (
                auto it_subshape = it_shape->begin(), it_color_vertex = it_color->begin();
                it_subshape != it_shape->end() && it_color_vertex != it_color->end();
                ++it_subshape, ++it_color_vertex
            ) {
                glColor3fv(it_color_vertex->data());
                glVertex3fv(it_subshape->data());
            }
            glEnd();
        }
    }


}
#endif // SHAPE_HPP