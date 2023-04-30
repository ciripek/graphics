#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <string>
#include <vector>

class DSAMesh final {
public:
    struct vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texcoord;
    };

    DSAMesh();
    ~DSAMesh();

    DSAMesh(const DSAMesh &) = delete;
    DSAMesh &operator=(DSAMesh &) = delete;

    DSAMesh(DSAMesh &&) = default;
    DSAMesh &operator=(DSAMesh &&) = default;

    void initBuffers();
    void draw() const;

    void addVertex(const vertex &vertex) {
        vertices.push_back(vertex);
    }

    void addIndex(GLuint index) {
        indices.push_back(index);
    }

private:
    GLuint vertexArrayObject{};
    GLuint vertexBuffer{};
    GLuint indexBuffer{};

    std::vector<vertex> vertices;
    std::vector<GLuint> indices;

    bool inited = false;
};
