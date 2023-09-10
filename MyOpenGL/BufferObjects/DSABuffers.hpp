#pragma once

#include <GL/glew.h>

#include <memory>
#include <ranges>
#include <stdexcept>
#include <vector>

#include "GLconversions.hpp"
#include "spdlog-config.hpp"

class DSABuffers {
 public:
  DSABuffers() = default;

  explicit DSABuffers(int num)
      : ids(std::make_unique<GLuint[]>(num)), num(num) {
    glCreateBuffers(num, ids.get());
  }

  ~DSABuffers() { clean(); }

  DSABuffers(const DSABuffers&) = delete;
  DSABuffers& operator=(const DSABuffers&) = delete;

  DSABuffers(DSABuffers&& rhs) noexcept
      : ids(std::move(rhs.ids)), num(std::exchange(rhs.num, 0)) {}

  DSABuffers& operator=(DSABuffers&& rhs) noexcept {
    if (this != &rhs) {
      clean();

      ids = std::move(rhs.ids);
      num = std::exchange(rhs.num, 0);
    }
    return *this;
  };

  void storage(GLsizeiptr size,
               const void* data,
               GLbitfield flags,
               int index = 0) {
    glNamedBufferStorage(ids[index], size, data, flags);
  }

  void storage(std::ranges::contiguous_range auto const& data,
               GLbitfield flags,
               int index = 0) {
    storage(ContainerSizeInBytes(data), std::ranges::data(data), flags, index);
  }

  void subData(std::ranges::contiguous_range auto const& data,
               GLintptr offset = 0,
               int index = 0) {
    subData(ContainerSizeInBytes(data), std::ranges::data(data), offset, index);
  }

  void subData(GLsizeiptr size,
               const void* data,
               GLintptr offset = 0,
               int index = 0) {
    glNamedBufferSubData(ids[index], offset, size, data);
  }

  void bindBufferBase(GLenum target, GLuint index, int i = 0) {
    glBindBufferBase(target, index, ids[i]);
  }

  int getBufferCount() const { return num; }

  GLuint operator[](size_t i) { return ids[i]; }

  GLuint at(size_t i) {
    if (i >= num) {
      throw std::out_of_range("Out of range");
    }
    return ids[i];
  }

  void clean() {
    if (ids != nullptr) {
      glDeleteBuffers(num, ids.get());
      num = 0;
      ids.reset(nullptr);
    }
  }

 private:
  std::unique_ptr<GLuint[]> ids;
  int num = 0;
};