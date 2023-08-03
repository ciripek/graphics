#pragma once

#include <GL/glew.h>

#include <utility>

#include "GLconversions.hpp"
#include "enums.hpp"

template<BufferType Target, BufferStorageUsage Usage>
class DSABufferStatic {
public:
    DSABufferStatic() { glCreateBuffers(1, &m_id); }
    ~DSABufferStatic() { glDeleteBuffers(1, &m_id); }

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
        if (m_id != 0 && m_sizeInBytes != 0) {
            glDeleteBuffers(1, &m_id);
        }
    }

    void storage(GLsizeiptr size, const void* data) const{
        glNamedBufferStorage(m_id, size, data, static_cast<GLbitfield>(Usage));
    }


    template<class T>
    void storage(const T &data) const{
        static_assert(HasContiguousStorage<T>::value, "Wrong Type of data container");

        storage(ContainerSizeInBytes(data), PointerToStart(data));
    }
    template<class T>
    void subData(const T &data, GLintptr offset = 0) const{
        static_assert(HasContiguousStorage<T>::value, "Wrong Type of data container");
        subData(ContainerSizeInBytes(data), PointerToStart(data), offset);
    }

    void subData(GLsizeiptr size, const void *data, GLintptr offset = 0) const {
        using enum BufferStorageUsage;

        if constexpr (isBitSet(Usage, DynamicStorageBit)){
            static_assert(false, "Wrong Usage");
        }

        glNamedBufferSubData(m_id, offset, size, data);
    }

    void bindBufferBase(GLenum target, GLuint index) const {
        using enum BufferType;

        if constexpr (Target == AtomicCounter || Target == TransformFeedback || Target == Uniform || Target == ShaderStorage){
            static_assert(false, "Wrong Target");
        }


        glBindBufferBase(target, index, m_id);
    }

    consteval BufferType getTarget() const {
        return Target;
    }

    consteval BufferStorageUsage getUsage() const {
        return Usage;
    };

private:
    GLuint m_id = 0;
    GLsizeiptr m_sizeInBytes = 0;

    static constexpr bool isBitSet(BufferStorageUsage bitfield, BufferStorageUsage bit){
        return static_cast<GLbitfield>(bitfield & bit) != 0U;
    }
};
