#ifndef OBJLOADER_HPP
#define OBJLOADER_HPP

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "shape.hpp"

#include <iostream>
namespace ObjLoader {
    Shape::Shape<glm::vec3, Shape::RGBColor> loadObjFile(const std::string &filePath) {
        // Placeholder implementation
        // Actual OBJ file parsing logic should be implemented here
        std::vector<glm::vec3> v;
        std::vector<glm::vec2> vt;
        std::vector<glm::vec3> vn;


        // Open File.
        std::ifstream objFile(filePath);

        if (!objFile.is_open()) {
            throw std::runtime_error("Failed to open OBJ file: " + filePath);
        }

        // Parse the OBJ file here and populate subshapes, colors, and drawMethods.
        Shape::Shape<glm::vec3, Shape::RGBColor> shape = Shape::Shape<glm::vec3, Shape::RGBColor>(
            std::vector<std::vector<glm::vec3>>(),
            std::vector<std::vector<Shape::RGBColor>>(),
            std::vector<GLenum>()
        );

        std::string line;
        while (std::getline(objFile, line)) {
            std::stringstream objFileLineStream(line);
            std::string prefix;

            objFileLineStream >> prefix;

            if (prefix == "#") {
                continue;
            }
            else if (prefix == "o") {
                // New object - ignored for now
            }
            else if (prefix == "v") {
                glm::vec3 V;
                objFileLineStream >> V.x >> V.y >> V.z;
                v.push_back(V * 10.0f); // Scale up for visibility
            }
            else if (prefix == "vt") {
                glm::vec2 VT;
                objFileLineStream >> VT.x >> VT.y;
                vt.push_back(VT);
            }
            else if (prefix == "vn") {
                glm::vec3 VN;
                objFileLineStream >> VN.x >> VN.y >> VN.z;
                vn.push_back(VN);
            }
            else if (prefix == "f") {
                // f <v1/t1/n1> <v2/t2/n2> <v3/t3/n3>
                std::vector<glm::vec3> faceVertices;
                std::vector<Shape::RGBColor> faceColors;
                std::string vertexString;
                while (objFileLineStream >> vertexString) { // V/T/N
                    std::stringstream vertexStream(vertexString);
                    std::string indexString;
                    std::vector<int> indices;
                    for (int idx = 0; std::getline(vertexStream, indexString, '/') && idx < 3; ++idx) { // End at 3 to avoid extra splits
                        if (!indexString.empty()) {
                            indices.push_back(std::stoi(indexString) - 1); // OBJ is 1-indexed
                        } else {
                            indices.push_back(-1); // No index
                        }
                    }

                    // Add vertex position
                    if (indices.size() > 0 && indices[0] >= 0 && indices[0] < v.size()) {
                        faceVertices.push_back(v[indices[0]]);
                    }
                    // For now, ignore texture coords and normals
                    // Assign a default color (white) for now
                    faceColors.push_back(Shape::RGBColor(1.0f, 1.0f, 1.0f));
                }
                shape.addSubShape(faceVertices, faceColors, GL_POLYGON);
            }
        }
        // std::cout << "Loaded OBJ file: " << filePath << " with "
        //           << v.size() << " vertices, "
        //           << vt.size() << " texture coords, "
        //           << vn.size() << " normals." << std::endl;
        return shape;
    }

}

#endif // OBJLOADER_HPP