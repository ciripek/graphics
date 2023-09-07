#pragma once

#include <GL/gl.h>
#include <GL/glew.h>

#include <vector>

#include "GLconversions.hpp"
#include "enums.hpp"

/*
        BufferType is an enum class that stands for OpenGL bind targets (from
   https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glBufferData.xhtml
   - OpenGL 4.6)
*/
template <BufferType target = BufferType::Array,
          BufferUsage usage = BufferUsage::StreamDraw>
class BufferObject final {
 public:
  BufferObject();
  ~BufferObject();

  BufferObject(const BufferObject&) = delete;
  BufferObject& operator=(const BufferObject&) = delete;

  BufferObject(BufferObject&& rhs);
  BufferObject& operator=(BufferObject&& rhs);

  template <typename T>
  explicit BufferObject(const std::vector<T>&);

  template <typename T, size_t N>
  explicit BufferObject(const std::array<T, N>&);

  operator unsigned int() const { return m_id; }

  void Clean();

  template <typename T>
  IsContiguousContainer<T> BufferData(const T& pArr);

  void BufferData(GLsizeiptr pSize, const GLvoid* pSource = nullptr);

  void BufferSubData(GLintptr pOffset,
                     GLsizeiptr pSize,
                     const GLvoid* pSource = nullptr);

  inline void Bind() const;

  template <typename T>
  BufferObject& operator=(const T& pArr);

  // returns a read-only copy of the buffer contents as an std::vector
  template <typename T>
  operator std::vector<T>() const;

  // returns a read-only copy of the buffer contents as an array
  template <typename T, size_t N>
  operator std::array<T, N>() const;

 private:
  GLuint m_id{};
  GLsizeiptr m_sizeInBytes{};
  static GLuint g_lastBound;
};

#include "BufferObject.inl"

using ArrayBuffer = BufferObject<>;
using IndexBuffer = BufferObject<BufferType::ElementArray>;
