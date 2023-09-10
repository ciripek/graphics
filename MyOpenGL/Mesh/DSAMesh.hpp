#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>
#include <string>
#include <utility>
#include <vector>

#include "ShaderProgram.hpp"
#include "tiny_obj_loader.h"

class DSAMesh final {
 public:
  struct vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texcoord;

    bool operator==(const DSAMesh::vertex& other) const = default;
  };

  int material_index;

  DSAMesh();
  ~DSAMesh();

  DSAMesh(const DSAMesh&) = delete;
  DSAMesh& operator=(DSAMesh&) = delete;

  DSAMesh(DSAMesh&& other) noexcept
      : vertexBuffer(std::exchange(other.vertexBuffer, 0)),
        indexBuffer(std::exchange(other.indexBuffer, 0)),
        vertices(std::move(other.vertices)),
        indices(std::move(other.indices)) {}

  DSAMesh& operator=(DSAMesh&&) = default;

  void initBuffers();

  void draw(GLuint vertexArrayObject,
            ShaderProgram& fragment,
            const std::unordered_map<std::string, GLuint>& textureMap,
            const std::vector<tinyobj::material_t>& materials);

  void addVertex(const vertex& vertex) { vertices.push_back(vertex); }

  int vertexSize() const { return vertices.size(); }

  void addIndex(GLuint index) { indices.push_back(index); }

  static GLuint initVao();

  static void deleteVao(GLuint vao);

 private:
  GLuint vertexBuffer{};
  GLuint indexBuffer{};

  std::vector<vertex> vertices;
  std::vector<GLuint> indices;
};
