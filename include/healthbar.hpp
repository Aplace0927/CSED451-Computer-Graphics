#ifndef HEALTHBAR_HPP
#define HEALTHBAR_HPP

#include "BBong/mesh3d.hpp"
#include "BBong/objfileloader.hpp"

namespace BBong {
inline std::shared_ptr<Mesh3D> createHealthBarMesh(int currentHealth, int maxHealth) {
    float xmin = -1.0f;
    float xmax = -1.0f + 2.0f * (static_cast<float>(currentHealth) / static_cast<float>(maxHealth));
    float height = 0.1f;

    std::vector<Vertex3D> vertices = {
        {glm::vec3(xmin, -height, -height), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
        {glm::vec3(xmin, -height,  height), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
        {glm::vec3(xmin,  height, -height), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
        {glm::vec3(xmin,  height,  height), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
        {glm::vec3(xmax, -height, -height), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
        {glm::vec3(xmax, -height,  height), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
        {glm::vec3(xmax,  height, -height), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
        {glm::vec3(xmax,  height,  height), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
    };
    std::vector<unsigned int> indices = {
        0, 2, 3, 1,
        4, 5, 7, 6,
        0, 1, 5, 4,
        2, 3, 7, 6,
        0, 2, 6, 4,
        1, 3, 7, 5,
    };
    return ObjFileLoader::loadFromVertex3D(vertices, indices);
  }
}

#endif // HEALTHBAR_HPP