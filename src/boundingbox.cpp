#include "boundingbox.hpp"

namespace BoundingBox {

    // Explicit specialization for BoundingBox<glm::vec3>
    template <>
    inline BoundingBox<glm::vec3>::BoundingBox() {
        GLfloat max = std::numeric_limits<GLfloat>::max();
        GLfloat min = std::numeric_limits<GLfloat>::min();
        start = glm::vec3(max, max, max);
        end = glm::vec3(min, min, min);
    }

    template<>
    inline bool BoundingBox<glm::vec3>::operator&(
        const BoundingBox<glm::vec3>& other
    ) const {
        for (int i = 0; i < 3; ++i) {
            if (not (end[i] < other.start[i] || start[i] > other.end[i])) {
                return true;    // Collides in dim i
            }
        }
        return false;   // No collision in any dimension
    }

    template <>
    inline void BoundingBox<glm::vec3>::draw() {
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
}