#pragma once

#include <GL/glew.h>

#include "DSABufferStatic.hpp"
#include "enums.hpp"

class DSAVertexArray {
 public:
  struct VertexInfo {
    GLuint attribindex;
    GLint size;
    GLenum type;
    GLboolean normalized;
    GLuint relativeoffset;
    GLuint bindingindex;
  };

  DELETE_COPY(DSAVertexArray)

  DSAVertexArray();
  ~DSAVertexArray();

  DSAVertexArray(DSAVertexArray&&) noexcept;
  DSAVertexArray& operator=(DSAVertexArray&&) noexcept;

  void clean() const;

  void enableVertexArrayAttrib(GLuint index) const;

  void vertexArrayAttribBinding(GLuint attribindex, GLuint bindingindex) const;

  void vertexArrayAttribFormat(GLuint attribindex,
                               GLint size,
                               GLenum type,
                               GLboolean normalized,
                               GLuint relativeoffset) const;

  void init(std::initializer_list<VertexInfo> vertexInfos) const;

  void vertexArrayVertexBuffer(GLuint bindingindex,
                               GLuint buffer,
                               GLintptr offset,
                               GLsizei stride) const;

  template <BufferStorageUsage Usage>
  void vertexArrayElementBuffer(
      const IndexBufferStatic<Usage>& index_buffer) const {
    glVertexArrayElementBuffer(id, index_buffer);
  }

  void bind() const;

  static void unbind();

 private:
  GLuint id = 0;
};