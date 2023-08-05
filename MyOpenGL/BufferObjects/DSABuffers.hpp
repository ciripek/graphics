#pragma once

#include <GL/glew.h>

#include <memory>
#include <stdexcept>
#include <vector>

#include "GLconversions.hpp"

class DSABuffers {
public:
    DSABuffers() = default;

    explicit DSABuffers(int num) : ids(std::make_unique<GLuint[]>(num)), num(num) {
        glCreateBuffers(num, ids.get());
    }

    ~DSABuffers() {
        if (ids != nullptr){
            glDeleteBuffers(num, ids.get());
        }
    }

    DSABuffers(const DSABuffers&) = delete;
    DSABuffers& operator=(const DSABuffers&) = delete;

    DSABuffers(DSABuffers&& rhs) noexcept = default;
    DSABuffers& operator=(DSABuffers&& rhs) noexcept = default;

    void storage(GLsizeiptr size, const void* data, GLbitfield flags, int index = 0){
        glNamedBufferStorage(ids[index], size, data, flags);
    }

    template<class T>
    void storage(const T& data, GLbitfield flags, int index = 0){
        static_assert(HasContiguousStorage_V<T>, "Wrong Type of data container");

        storage(ContainerSizeInBytes(data), PointerToStart(data), flags, index);
    }

    template<class T>
    void subData(const T& data, GLintptr offset = 0, int index = 0){
        static_assert(HasContiguousStorage_V<T>, "Wrong Type of data container");

        subData(ContainerSizeInBytes(data), PointerToStart(data), offset, index);
    }

    void subData(GLsizeiptr size, const void *data, GLintptr offset = 0, int index = 0){
        glNamedBufferSubData(ids[index], offset, size, data);
    }

    void bindBufferBase(GLenum target, GLuint index, int i = 0){
        glBindBufferBase(target, index, ids[i]);
    }

    int getBufferCount() const { return num; }

    GLuint operator[](size_t i) { return ids[i]; }

    GLuint at(size_t i){
        if (i >= num){
            throw std::out_of_range("Out of range");
        }
    }
private:
    std::unique_ptr<GLuint[]> ids;
    int num = 0;

};