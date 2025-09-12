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
            for (auto& subshape : subshapes) {
                for (auto& vertex : subshape) {
                    for (size_t i = 0; i < D; ++i) {
                        vertex[i] += displacement[i];
                    }
                }
            }
        }

        BoundingBox::BoundingBox<T, D> getBoundingBox() const {
            // Compute and return the bounding box based on subshapes
            std::array<T, D> minPoint, maxPoint;
            minPoint.fill(std::numeric_limits<T>::max());
            maxPoint.fill(std::numeric_limits<T>::min());

            for (const auto& subshape : subshapes) {
                for (const auto& vertex : subshape) {
                    for (size_t i = 0; i < D; ++i) {
                        if (vertex[i] < minPoint[i]) minPoint[i] = vertex[i];
                        if (vertex[i] > maxPoint[i]) maxPoint[i] = vertex[i];
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
        for (size_t subShapeIdx = 0; subShapeIdx < subshapes.size(); ++subShapeIdx) {
            glBegin(drawMethod[subShapeIdx]);
            for (size_t subVertexIdx = 0; subVertexIdx < subshapes[subShapeIdx].size(); ++subVertexIdx) {
                glColor3fv(colors[subShapeIdx][subVertexIdx].data());
                glVertex3fv(subshapes[subShapeIdx][subVertexIdx].data());
            }
            glEnd();
        }
    }


}
#endif // SHAPE_HPP