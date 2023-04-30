#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <vector>

class Mesh final {
public:
    struct vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texcoord;
    };

    Mesh();
    ~Mesh();

    Mesh(const Mesh &) = delete;
    Mesh &operator=(Mesh &) = delete;

    Mesh(Mesh &&) = default;
    Mesh &operator=(Mesh &&) = default;

    void initBuffers();
    void draw();

    void addVertex(const vertex &vertex) {
        vertices.push_back(vertex);
    }

    void addIndex(unsigned int index) {
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
