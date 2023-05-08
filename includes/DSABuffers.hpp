#pragma once

#include <GL/glew.h>

#include <memory>
#include <stdexcept>
#include <array>
#include <vector>

class DSABuffers {
public:
    explicit DSABuffers(int num = 1) : ids(std::make_unique<GLuint[]>(num)), num(num) {
        glCreateBuffers(num, ids.get());
    }

    ~DSABuffers() {
        glDeleteBuffers(num, ids.get());
    }

    void storage(GLsizeiptr size, const void* data, GLbitfield flags, int index = 0){
        glNamedBufferStorage(ids[index], size, data, flags);
    }

    template<class T, size_t N>
    void storage(std::array<T, N> data, GLbitfield flags, int index = 0){
        storage(data.size() * sizeof(T), data.data(), flags, index);
    }

    template<class T>
    void storage(std::vector<T> data, GLbitfield flags, int index = 0){
        storage(data.size() * sizeof(T), data.data(), flags, index);
    }

    template<class T, size_t N>
    void subData(std::array<T, N> data, GLintptr offset = 0, int index = 0){
        subData(data.size() * sizeof(T), data.data(), offset, index);
    }

    template<class T>
    void subData(std::vector<T> data, GLintptr offset = 0, int index = 0){
        subData(data.size() * sizeof(T), data.data(), offset, index);
    }

    void subData(GLsizeiptr size, const void *data, GLintptr offset = 0, int index = 0){
        glBufferSubData(ids[index], offset, size, data);
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
    const int num;
};