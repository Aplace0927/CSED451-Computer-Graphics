#include "shape.hpp"

namespace Shape {

    // Explicit specialization for Shape<glm::vec3, RGBColor>

    template <>
    inline Shape<glm::vec3, RGBColor>::Shape(
        const std::vector<std::vector<glm::vec3>>& _subshapes,
        const std::vector<std::vector<RGBColor>>& _colors,
        const std::vector<unsigned int>& _drawMethod
    ): subshapes(_subshapes), colors(_colors), drawMethod(_drawMethod) {
        center = glm::vec3(0.0f, 0.0f, 0.0f);
    }

    template <>
    inline void Shape<glm::vec3, RGBColor>::draw() {
        typename std::vector<std::vector<glm::vec3>>::const_iterator it_drawing;
        typename std::vector<std::vector<RGBColor>>::const_iterator it_coloring;
        typename std::vector<unsigned int>::const_iterator it_method;

        typename std::vector<glm::vec3>::const_iterator it_shape;
        typename std::vector<RGBColor>::const_iterator it_color_vertex;;
        for (
            it_drawing = subshapes.begin(), it_coloring = colors.begin(), it_method = drawMethod.begin();
            it_drawing != subshapes.end() && it_coloring != colors.end() && it_method != drawMethod.end();
            ++it_drawing, ++it_coloring, ++it_method
        ) {
            glBegin(*it_method);
            for (
                it_shape = it_drawing->begin(), it_color_vertex = it_coloring->begin();
                it_shape != it_drawing->end() && it_color_vertex != it_coloring->end();
                ++it_shape, ++it_color_vertex
            ) {
                glColor3fv(glm::value_ptr(*it_color_vertex));
                glVertex3fv(glm::value_ptr(*it_shape));
            }
            glEnd();
        }
    }

    template <>
    inline BoundingBox::BoundingBox<glm::vec3> Shape<glm::vec3, RGBColor>::getBoundingBox() const {
            GLfloat max = std::numeric_limits<GLfloat>::max();
            GLfloat min = std::numeric_limits<GLfloat>::min();
            
            glm::vec3 minPoint(max, max, max);
            glm::vec3 maxPoint(min, min, min);

            for (const auto& subshape : subshapes) {
                for (const auto& vertex : subshape) {
                    minPoint = glm::min(minPoint, vertex);
                    maxPoint = glm::max(maxPoint, vertex);
                }
            }
            return BoundingBox::BoundingBox<glm::vec3>(minPoint, maxPoint);
    }

    template <>
    inline BoundingBox::BoundingBox<glm::vec3> Shape<glm::vec3, RGBColor>::move(
        const glm::vec3& displacement
    ) {
        glm::mat4x4 translationMatrix = glm::translate(
            glm::identity<glm::mat4>(),
            displacement
        );
        glm::vec4 translatedVec;

        for (auto& subshape: subshapes) {
            for (auto& vertex: subshape) {
                translatedVec = translationMatrix * glm::vec4(vertex, 1.0f);
                vertex = translatedVec / translatedVec.w;
            }
        }

        translatedVec = translationMatrix * glm::vec4(center, 1.0f);
        center = translatedVec / translatedVec.w;
        return getBoundingBox();
    }

    template <>
    inline BoundingBox::BoundingBox<glm::vec3> Shape<glm::vec3, RGBColor>::rotate(
        const glm::vec3 &rotation,
        const glm::vec3 &pivot
    ) {
        glm::mat4x4 rotationMatrix = glm::identity<glm::mat4>();
        rotationMatrix = glm::rotate(rotationMatrix, rotation[0], glm::vec3(1.f, 0.f, 0.f));
        rotationMatrix = glm::rotate(rotationMatrix, rotation[1], glm::vec3(0.f, 1.f, 0.f));
        rotationMatrix = glm::rotate(rotationMatrix, rotation[2], glm::vec3(0.f, 0.f, 1.f));
    
        glm::vec4 pivotVec;
        glm::vec4 rotatedVec;
        for (auto& subshape: subshapes) {
            for (auto& vertex: subshape) {
                pivotVec = glm::vec4(vertex - pivot, 1.0f);
                rotatedVec = rotationMatrix * pivotVec;
                rotatedVec /= rotatedVec.w; // Normalize

                vertex = glm::vec3(rotatedVec) + pivot;
            }
        }

        pivotVec = glm::vec4(center - pivot, 1.0f);
        rotatedVec = rotationMatrix * pivotVec;
        rotatedVec /= rotatedVec.w; // Normalize
        center = glm::vec3(rotatedVec) + pivot;
        return getBoundingBox();
    }
}