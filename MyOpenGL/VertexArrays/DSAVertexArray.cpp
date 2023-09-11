#include "DSAVertexArray.hpp"

#include <utility>

DSAVertexArray::DSAVertexArray() {
  glCreateVertexArrays(1, &id);
}

DSAVertexArray::~DSAVertexArray() {
  clean();
}

void DSAVertexArray::clean() const {
  if (id != 0) {
    glDeleteVertexArrays(1, &id);
  }
}

DSAVertexArray::DSAVertexArray(DSAVertexArray&& rhs) noexcept
    : id(std::exchange(rhs.id, 0)) {}

DSAVertexArray& DSAVertexArray::operator=(DSAVertexArray&& rhs) noexcept {
  if (&rhs != this) {
    clean();

    id = std::exchange(rhs.id, 0);
  }

  return *this;
}

void DSAVertexArray::enableVertexArrayAttrib(GLuint index) const {
  glEnableVertexArrayAttrib(id, index);
}

void DSAVertexArray::vertexArrayAttribBinding(GLuint attribindex,
                                              GLuint bindingindex) const {
  glVertexArrayAttribBinding(id, attribindex, bindingindex);
}

void DSAVertexArray::vertexArrayAttribFormat(GLuint attribindex,
                                             GLint size,
                                             GLenum type,
                                             GLboolean normalized,
                                             GLuint relativeoffset) const {
  glVertexArrayAttribFormat(id, attribindex, size, type, normalized,
                            relativeoffset);
}

void DSAVertexArray::init(std::initializer_list<VertexInfo> vertexInfos) const {
  for (const auto& vertexInfo : vertexInfos) {
    enableVertexArrayAttrib(vertexInfo.attribindex);
    vertexArrayAttribBinding(vertexInfo.attribindex, vertexInfo.bindingindex);
    vertexArrayAttribFormat(vertexInfo.attribindex, vertexInfo.size,
                            vertexInfo.type, vertexInfo.normalized,
                            vertexInfo.relativeoffset);
  }
}

void DSAVertexArray::vertexArrayVertexBuffer(GLuint bindingindex,
                                             GLuint buffer,
                                             GLintptr offset,
                                             GLsizei stride) const {
  glVertexArrayVertexBuffer(id, bindingindex, buffer, offset, stride);
}

void DSAVertexArray::bind() const {
  glBindVertexArray(id);
}

void DSAVertexArray::unbind() {
  glBindVertexArray(0);
}
