#include "DSAMesh.hpp"

#include <assimp/scene.h>
#include "ShaderProgram.hpp"

DSAMesh::DSAMesh() = default;

DSAMesh::~DSAMesh() {
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &indexBuffer);
}

void DSAMesh::initBuffers(){
    glCreateBuffers(1, &vertexBuffer);
    glNamedBufferStorage(vertexBuffer, sizeof(vertex) * vertices.size(), vertices.data(), 0);

    glCreateBuffers(1, &indexBuffer);
    glNamedBufferStorage(indexBuffer, sizeof(GLuint) * indices.size(), indices.data(), 0);
}

GLuint DSAMesh::initVao(){
    GLuint vertexArrayObject{};
    glCreateVertexArrays(1, &vertexArrayObject);

    glEnableVertexArrayAttrib(vertexArrayObject, 0);
    glEnableVertexArrayAttrib(vertexArrayObject, 1);
    glEnableVertexArrayAttrib(vertexArrayObject, 2);

    glVertexArrayAttribBinding(vertexArrayObject, 0, 0);
    glVertexArrayAttribBinding(vertexArrayObject, 1, 0);
    glVertexArrayAttribBinding(vertexArrayObject, 2, 0);

    glVertexArrayAttribFormat(vertexArrayObject, 0, 3, GL_FLOAT, GL_FALSE, offsetof(vertex, position));
    glVertexArrayAttribFormat(vertexArrayObject, 1, 3, GL_FLOAT, GL_FALSE, offsetof(vertex, normal));
    glVertexArrayAttribFormat(vertexArrayObject, 2, 2, GL_FLOAT, GL_FALSE, offsetof(vertex, texcoord));


    return vertexArrayObject;
}

void DSAMesh::draw(GLuint vertexArrayObject) const{
    glBindVertexArray(vertexArrayObject);

    glVertexArrayVertexBuffer(vertexArrayObject, 0, vertexBuffer, 0, sizeof(vertex));
    glVertexArrayElementBuffer(vertexArrayObject, indexBuffer);

    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, nullptr);

    glBindVertexArray(0);
}

void DSAMesh::deleteVao(GLuint vao) {
    glDeleteVertexArrays(1, &vao);
}
