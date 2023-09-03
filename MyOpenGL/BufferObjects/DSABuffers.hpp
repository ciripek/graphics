#pragma once

#include <GL/glew.h>

#include <memory>
#include <stdexcept>
#include <vector>
#include <ranges>

#include "GLconversions.hpp"
#include "spdlog-config.hpp"

class DSABuffers {
public:
#ifndef NDEBUG
    DSABuffers() {
        SPDLOG_INFO("Default DSABuffers created");
    }
#else
    DSABuffers() = default;
#endif

    explicit DSABuffers(int num) : ids(std::make_unique<GLuint[]>(num)), num(num) {
        SPDLOG_INFO("DSABuffers created with {} param", num);
        glCreateBuffers(num, ids.get());
    }

    ~DSABuffers() {
        SPDLOG_INFO("DSABUffers destroyed with {}", num);
        glDeleteBuffers(num, ids.get());
    }

    DSABuffers(const DSABuffers&) = delete;
    DSABuffers& operator=(const DSABuffers&) = delete;

    DSABuffers(DSABuffers&& rhs) noexcept : ids(std::move(rhs.ids)), num(std::exchange(rhs.num, 0)) {
        SPDLOG_INFO("DSABuffer move created with {} param", num);
    }
    DSABuffers& operator=(DSABuffers&& rhs) noexcept {
        if (this != &rhs)
        {
            ids = std::move(rhs.ids);
            num = std::exchange(rhs.num, 0);
            SPDLOG_INFO("DSABuffer move created with {} param", num);
        }
        return *this;
    };

    void storage(GLsizeiptr size, const void* data, GLbitfield flags, int index = 0){
        glNamedBufferStorage(ids[index], size, data, flags);
    }

    void storage(std::ranges::contiguous_range auto const& data, GLbitfield flags, int index = 0){
        storage(ContainerSizeInBytes(data), std::ranges::data(data), flags, index);
    }

    void subData(std::ranges::contiguous_range auto const& data, GLintptr offset = 0, int index = 0){
        subData(ContainerSizeInBytes(data), std::ranges::data(data), offset, index);
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
        return ids[i];
    }
private:
    std::unique_ptr<GLuint[]> ids;
    int num = 0;

};