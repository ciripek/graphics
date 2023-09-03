#pragma once

#include <GL/glew.h>
#include <ranges>

#include <utility>

#include "GLconversions.hpp"
#include "enums.hpp"

template<BufferType Target, BufferStorageUsage Usage>
class DSABufferStatic {
public:
    DSABufferStatic() { glCreateBuffers(1, &m_id); }
    ~DSABufferStatic() { clean();}

    DELETE_COPY(DSABufferStatic)

    DSABufferStatic(DSABufferStatic &&rhs) noexcept: m_id(std::exchange(rhs.m_id, 0)),
                                                     m_sizeInBytes(std::exchange(rhs.m_sizeInBytes, 0)) {}

    DSABufferStatic &operator=(DSABufferStatic &&rhs) noexcept {
        if (&rhs == this) return *this;

        clean();

        m_id = std::exchange(rhs.m_id, 0);
        m_sizeInBytes = std::exchange(rhs.m_sizeInBytes, 0);
    }

    void clean() {
        if (m_id != 0) {
            glDeleteBuffers(1, &m_id);
            m_id = 0;
            m_sizeInBytes = 0;
        }
    }

    void storage(GLsizeiptr size, const void* data){
        m_sizeInBytes = size;
        glNamedBufferStorage(m_id, size, data, static_cast<GLbitfield>(Usage));
    }


    template<std::ranges::contiguous_range T>
    void storage(const T &data){
        storage(ContainerSizeInBytes(data), std::ranges::data(data));
    }
    template<class T>
    void subData(const T &data, GLintptr offset = 0) const{
        static_assert(HasContiguousStorage_V<T>, "Wrong Type of data container");
        subData(ContainerSizeInBytes(data), PointerToStart(data), offset);
    }

    void subData(GLsizeiptr size, const void *data, GLintptr offset = 0) const {
        using enum BufferStorageUsage;
        static_assert(!isBitSet(Usage, DynamicStorageBit), "Wrong Usage");

        glNamedBufferSubData(m_id, offset, size, data);
    }

    void bindBufferBase(GLuint index) const {
        using enum BufferType;

        static_assert(!(Target == AtomicCounter || Target == TransformFeedback || Target == Uniform || Target == ShaderStorage)
                , "Wrong Target");

        glBindBufferBase(static_cast<GLenum>(Target), index, m_id);
    }

    consteval BufferType getTarget() const {
        return Target;
    }

    consteval BufferStorageUsage getUsage() const {
        return Usage;
    };

    operator GLuint() const {
        return m_id;
    };

    template<typename T>
    operator std::vector<T>()
    {
        T* ptr = static_cast<T*>(glMapNamedBuffer(m_id, GL_READ_ONLY));

        std::vector<T> ret(ptr, ptr + m_sizeInBytes / sizeof(T));
        glUnmapNamedBuffer(m_id);
        return ret;
    }

private:
    GLuint m_id = 0;
    GLuint m_sizeInBytes = 0;
};
