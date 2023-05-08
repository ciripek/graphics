#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>
#include <string>
#include <utility>
#include <vector>

#include "Material.hpp"
#include "ShaderProgram.hpp"
#include "tiny_obj_loader.h"



class DSAMesh final {
public:
    struct vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texcoord;

        bool operator==(const DSAMesh::vertex &other) const = default;
    };




    DSAMesh();
    ~DSAMesh();

    DSAMesh(const DSAMesh &) = delete;
    DSAMesh &operator=(DSAMesh &) = delete;

    DSAMesh(DSAMesh &&other) noexcept : vertexBuffer(std::exchange(other.vertexBuffer, 0)),
                               indexBuffer(std::exchange(other.indexBuffer, 0)),
                               vertices(std::move(other.vertices)),
                               indices(std::move(other.indices)) {}

    DSAMesh &operator=(DSAMesh &&) = default;

    void initBuffers();

    void draw(GLuint vertexArrayObject) const;

    void addVertex(const vertex &vertex) {
        vertices.push_back(vertex);
    }

    int vertexSize() const {
        return vertices.size();
    }

    void addIndex(GLuint index) {
        indices.push_back(index);
    }

    static GLuint initVao();

    static void deleteVao(GLuint vao);

    void setMaterial(const tinyobj::material_t &mat) {
        material_t = mat;
    }

private:
    GLuint vertexBuffer{};
    GLuint indexBuffer{};

    std::vector<vertex> vertices;
    std::vector<GLuint> indices;
    tinyobj::material_t material_t;
};

template<>
struct std::hash<DSAMesh::vertex>
{
    std::size_t operator()(const DSAMesh::vertex& v) const noexcept
    {
        using std::size_t;
        using std::hash;
        using std::string;

        return ((hash<glm::vec3>()(v.position)
                 ^ (hash<glm::vec3>()(v.normal) << 1)) >> 1)
               ^ (hash<glm::vec2>()(v.texcoord) << 1);
    }
};
