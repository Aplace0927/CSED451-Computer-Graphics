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
            center.fill((T)0);
        }

        std::array<T, D> getCenter() const {
            return center;
        }

        virtual BoundingBox::BoundingBox<T, D> move(const std::array<T, D>& displacement) {throw std::runtime_error("move() not implemented for this Shape specialization");};
        virtual BoundingBox::BoundingBox<T, D> rotate(
            const std::array<T, D>& rotation,
            const std::array<T, D>& pivot
        ) {throw std::runtime_error("rotate() not implemented for this Shape specialization");};

        virtual void draw() {throw std::runtime_error("draw() not implemented for this Shape specialization");};

    private:
        std::array<T, D> center;
        std::vector<std::vector<std::array<T, D>>> subshapes;
        std::vector<std::vector<C>> colors;
        std::vector<unsigned int> drawMethod;        

        BoundingBox::BoundingBox<T, D> getBoundingBox() const {
            // Compute and return the bounding box based on subshapes
            typename std::array<T, D>::iterator it_min, it_max;
            typename std::array<T, D>::const_iterator it_v;

            std::array<T, D> minPoint, maxPoint;
            minPoint.fill(std::numeric_limits<T>::max());
            maxPoint.fill(std::numeric_limits<T>::min());

            for (const auto& subshape : subshapes) {
                for (const auto& vertex : subshape) {
                    for (size_t dim = 0; dim < D; ++dim) {
                        minPoint[dim] = std::min(minPoint[dim], vertex[dim]);
                        maxPoint[dim] = std::max(maxPoint[dim], vertex[dim]);
                    }
                }
            }
            return BoundingBox::BoundingBox<T, D>(minPoint, maxPoint);
        }
    };

    // Explicit specialization for Shape<float, 3, RGBColor>
    template <>
    inline void Shape<float, 3, RGBColor>::draw() {
        std::vector<unsigned int>::iterator it_d = drawMethod.begin();
        std::vector<std::vector<std::array<float, 3>>>::iterator it_shape = subshapes.begin();
        std::vector<std::array<float, 3>>::iterator it_subshape;
        std::vector<std::vector<RGBColor>>::iterator it_color = colors.begin();
        std::vector<RGBColor>::iterator it_color_vertex;
        for (
            ; it_d != drawMethod.end() && it_shape != subshapes.end() && it_color != colors.end();
            ++it_d, ++it_shape, ++it_color
        ) {
            glBegin(*it_d);
            for (
                it_subshape = it_shape->begin(), it_color_vertex = it_color->begin();
                it_subshape != it_shape->end() && it_color_vertex != it_color->end();
                ++it_subshape, ++it_color_vertex
            ) {
                glColor3fv(it_color_vertex->data());
                glVertex3fv(it_subshape->data());
            }
            glEnd();
        }
    }

    template <>
    inline BoundingBox::BoundingBox<float, 3> Shape<float, 3, RGBColor>::move(
        const std::array<float, 3>& displacement
    ) {
        glm::mat4x4 translationMatrix = glm::translate(
            glm::identity<glm::mat4>(),
            glm::make_vec3(displacement.data())
        );
        glm::vec4 translatedVec;

        for (auto& subshape: subshapes) {
            for (auto& vertex: subshape) {
                translatedVec = translationMatrix * glm::vec4(vertex[0], vertex[1], vertex[2], 1.0f);
                translatedVec /= translatedVec.w; // Normalize

                for(size_t i = 0; i < 3; ++i) {
                    vertex[i] = translatedVec[i];
                }
            }
        }

        translatedVec = translationMatrix * glm::vec4(center[0], center[1], center[2], 1.0f);
        translatedVec /= translatedVec.w; // Normalize
        for(size_t i = 0; i < 3; ++i) {
            center[i] = translatedVec[i];
        }
        return getBoundingBox();
    }

    template <>
    inline BoundingBox::BoundingBox<float, 3> Shape<float, 3, RGBColor>::rotate(
        const std::array<float, 3> &rotation,
        const std::array<float, 3> &pivot
    ) {
        glm::mat4x4 rotationMatrix = glm::identity<glm::mat4>();
        rotationMatrix = glm::rotate(rotationMatrix, rotation[0], glm::vec3(1.f, 0.f, 0.f));
        rotationMatrix = glm::rotate(rotationMatrix, rotation[1], glm::vec3(0.f, 1.f, 0.f));
        rotationMatrix = glm::rotate(rotationMatrix, rotation[2], glm::vec3(0.f, 0.f, 1.f));
    
        glm::vec4 pivotVec;
        glm::vec4 rotatedVec;
        for (auto& subshape: subshapes) {
            for (auto& vertex: subshape) {
                pivotVec = glm::vec4(vertex[0] - pivot[0], vertex[1] - pivot[1], vertex[2] - pivot[2], 1.0f);
                rotatedVec = rotationMatrix * pivotVec;
                rotatedVec /= rotatedVec.w; // Normalize

                for(size_t i = 0; i < 3; ++i) {
                    vertex[i] = rotatedVec[i] + pivot[i];
                }
            }
        }

        pivotVec = glm::vec4(center[0] - pivot[0], center[1] - pivot[1], center[2] - pivot[2], 1.0f);
        rotatedVec = rotationMatrix * pivotVec;
        rotatedVec /= rotatedVec.w; // Normalize
        for(size_t i = 0; i < 3; ++i) {
            center[i] = rotatedVec[i] + pivot[i];
        }
        return getBoundingBox();
    }
}
#endif // SHAPE_HPP