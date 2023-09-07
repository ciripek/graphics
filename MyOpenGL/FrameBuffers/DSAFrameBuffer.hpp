#pragma once

#include <GL/glew.h>

#include <memory>

class DSAFrameBuffer {
 public:
  DSAFrameBuffer() = default;

  explicit DSAFrameBuffer(int num)
      : ids(std::make_unique<GLuint[]>(num)), num(num) {
    glCreateFramebuffers(num, ids.get());
  }

  ~DSAFrameBuffer() {
    if (ids) {
      glDeleteFramebuffers(num, ids.get());
    }
  }

 private:
  std::unique_ptr<GLuint[]> ids;
  int num = 0;
};
