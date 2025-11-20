#include "BBong/objfileloader.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

namespace BBong {
unsigned int
ObjFileLoader::processVertex(const std::string &vertexData,
                             const std::vector<glm::vec3> &temp_positions,
                             const std::vector<glm::vec2> &temp_texCoords,
                             const std::vector<glm::vec3> &temp_normals,
                             std::vector<Vertex3D> &out_vertices,
                             std::map<std::string, unsigned int> &vertexMap) {
  if (vertexMap.find(vertexData) != vertexMap.end()) {
    return vertexMap[vertexData];
  }

  Vertex3D vertex;
  unsigned int newIndex = out_vertices.size();

  std::stringstream ss(vertexData);
  std::string segment;
  int indices[3] = {0, 0, 0};
  int i = 0;

  while (std::getline(ss, segment, '/') && i < 3) {
    if (!segment.empty()) {
      indices[i] = std::stoi(segment);
    }
    i++;
  }

  if (indices[0] > 0)
    vertex.position = temp_positions[indices[0] - 1];
  if (indices[1] > 0)
    vertex.texCoord = temp_texCoords[indices[1] - 1];
  if (indices[2] > 0)
    vertex.normal = temp_normals[indices[2] - 1];

  out_vertices.push_back(vertex);
  vertexMap[vertexData] = newIndex;
  return newIndex;
}

std::shared_ptr<Mesh3D> ObjFileLoader::load(const std::string &path) {
  std::ifstream file(path);
  if (!file.is_open()) {
    std::cerr << "Error: Could not open OBJ file: " << path << std::endl;
    return nullptr;
  }

  std::vector<glm::vec3> temp_positions;
  std::vector<glm::vec2> temp_texCoords;
  std::vector<glm::vec3> temp_normals;

  std::vector<Vertex3D> out_vertices;
  std::vector<unsigned int> out_indices;

  std::map<std::string, unsigned int> vertexMap;

  std::string line;
  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string prefix;
    ss >> prefix;

    if (prefix == "v") {
      glm::vec3 pos;
      ss >> pos.x >> pos.y >> pos.z;
      temp_positions.push_back(pos); // Scale up for visibility
    } else if (prefix == "vt") {
      glm::vec2 uv;
      ss >> uv.x >> uv.y;
      temp_texCoords.push_back(uv);
    } else if (prefix == "vn") {
      glm::vec3 norm;
      ss >> norm.x >> norm.y >> norm.z;
      temp_normals.push_back(norm);
    } else if (prefix == "f") {
      std::string vertexData;
      std::vector<unsigned int> faceIndices;

      while (ss >> vertexData) {
        faceIndices.push_back(processVertex(vertexData, temp_positions,
                                            temp_texCoords, temp_normals,
                                            out_vertices, vertexMap));
      }

      for (size_t i = 1; i < faceIndices.size() - 1; ++i) {
        out_indices.push_back(faceIndices[0]);
        out_indices.push_back(faceIndices[i]);
        out_indices.push_back(faceIndices[i + 1]);
      }
    }
  }
  file.close();

  GLuint m_vao;
  VBOProps m_vbo;

  /* Debug here */
  glGenVertexArrays(1, &m_vao);

  glGenBuffers(1, &m_vbo.vboVertices);
  glBindVertexArray(m_vao);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo.vboVertices);
  glBufferData(
    GL_ARRAY_BUFFER,
    static_cast<GLsizeiptr>(out_vertices.size() * sizeof(Vertex3D)),
    out_vertices.data(),
    GL_STATIC_DRAW
  );

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(
    0,
    3,
    GL_FLOAT,
    GL_FALSE,
    sizeof(Vertex3D),
    (void*)offsetof(Vertex3D, position)
  );
  
  glGenBuffers(1, &m_vbo.vboNormal);
  glBindVertexArray(m_vao);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo.vboNormal);
  glBufferData(
    GL_ARRAY_BUFFER,
    static_cast<GLsizeiptr>(out_indices.size() * sizeof(unsigned int)),
    out_indices.data(),
    GL_STATIC_DRAW
  );
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(
    1,
    3,
    GL_FLOAT,
    GL_FALSE,
    sizeof(Vertex3D),
    (void*)offsetof(Vertex3D, normal)
  );


  glBindVertexArray(0);

  std::shared_ptr<Mesh3D> mesh = std::make_shared<Mesh3D>(out_vertices, out_indices);
  mesh->setVAO(m_vao);
  mesh->setVBO(m_vbo);

  std::cerr << "Loaded OBJ file: " << path << " with "
            << out_vertices.size() << " vertices." << 
            "(VAO: " << m_vao << ", VBO Vert: " << m_vbo.vboVertices << ", VBO Normal: " << m_vbo.vboNormal << ")\n"; 
  return mesh;
}
} // namespace BBong