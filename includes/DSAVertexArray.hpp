#pragma once

#include <GL/glew.h>

#include <memory>
#include <initializer_list>

class DSAVertexArrays {
public:
    struct VertexInfo{
        GLuint attribindex;
        GLint size;
        GLenum type;
        GLboolean normalized;
        GLuint relativeoffset;
        GLuint bindingindex;
    };

    explicit DSAVertexArrays(int num) : ids(std::make_unique<GLuint[]>(num)), num(num){
        glCreateVertexArrays(num, ids.get());
    }

    ~DSAVertexArrays(){
        glDeleteVertexArrays(num, ids.get());
    }

    void enableVertexArrayAttrib(GLuint index, int i = 0){
        glEnableVertexArrayAttrib(ids[i], index);
    }

    void vertexArrayAttribBinding(GLuint attribindex, GLuint bindingindex, int i = 0){
        glVertexArrayAttribBinding(ids[i], attribindex, bindingindex);
    }

    void vertexArrayAttribFormat(GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset, int i = 0){
        glVertexArrayAttribFormat(ids[i], attribindex, size, type, normalized, relativeoffset);
    }

    void init(std::initializer_list<VertexInfo> vertexInfos, int i = 0){
        for (const auto& vertexInfo: vertexInfos) {
            enableVertexArrayAttrib(vertexInfo.attribindex);
            vertexArrayAttribBinding(vertexInfo.attribindex, vertexInfo.bindingindex);
            vertexArrayAttribFormat(vertexInfo.attribindex, vertexInfo.size, vertexInfo.type, vertexInfo.normalized, vertexInfo.relativeoffset, i);
        }
    }

    void vertexArrayVertexBuffer(GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride, int i = 0){
        glVertexArrayVertexBuffer(ids[i], bindingindex, buffer, offset, stride);
    }

    void vertexArrayElementBuffer(GLuint buffer, int i = 0){
        glVertexArrayElementBuffer(ids[0], buffer);
    }

    void bind(int i = 0){
        glBindVertexArray(ids[i]);
    }

    static void unbind(){
        glBindVertexArray(0);
    }

private:
    std::unique_ptr<GLuint[]> ids;
    int num = 0;
};