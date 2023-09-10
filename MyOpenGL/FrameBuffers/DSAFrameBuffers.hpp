#pragma once

#include <GL/glew.h>

#include <memory>

class DSAFrameBuffers {
 public:
  DSAFrameBuffers() = default;

  explicit DSAFrameBuffers(int num)
      : ids(std::make_unique<GLuint[]>(num)), num(num) {
    glCreateFramebuffers(num, ids.get());
  }

  ~DSAFrameBuffers() {
    if (ids) {
      glDeleteFramebuffers(num, ids.get());
    }
  }

 private:
  std::unique_ptr<GLuint[]> ids;
  int num = 0;
};
