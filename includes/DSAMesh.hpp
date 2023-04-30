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
    void draw();

    void addVertex(const vertex &vertex) {
        vertices.push_back(vertex);
    }

    void addIndex(unsigned int index) {
        indices.push_back(index);
    }

    static DSAMesh* load(const std::string& file_name);

private:
    GLuint vertexArrayObject{};
    GLuint vertexBuffer{};
    GLuint indexBuffer{};

    std::vector<vertex> vertices;
    std::vector<GLuint> indices;

    bool inited = false;

    void loadModel(const std::string& file_name);
};
