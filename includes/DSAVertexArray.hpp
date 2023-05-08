#pragma once

#include <GL/glew.h>

#include <array>

template<size_t size>
class DSAVertexArrays {
public:
    DSAVertexArrays() {
        glCreateVertexArrays(size, ids.data());
    }

    ~DSAVertexArrays(){
        glDeleteVertexArrays(size, &ids);
    }

private:
    std::array<GLuint, size> ids;
};