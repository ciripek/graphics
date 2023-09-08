#pragma once

#include <GL/glew.h>

#include <array>
#include <utility>

#include "enums.hpp"

template <size_t size = 1>
class ProgramPipelines {
 public:
  explicit ProgramPipelines() { glCreateProgramPipelines(size, ids.data()); }

  ~ProgramPipelines() { glDeleteProgramPipelines(size, ids.data()); }

  DELETE_COPY(ProgramPipelines);

  ProgramPipelines(ProgramPipelines&& other) noexcept
      : ids(std::exchange(other.ids, {})) {}

  ProgramPipelines& operator=(ProgramPipelines&& other) noexcept {
    if (this != &other) {
      ids = std::exchange(other.ids, {});
    }

    return *this;
  };

  void activeShaderProgram(GLuint program, int num = 0) const {
    glActiveShaderProgram(ids[num], program);
  }

  void bind(int num = 0) const { glBindProgramPipeline(ids[num]); }

  static void unbind() { glBindProgramPipeline(0); }
  void validate(int num = 0) const { glValidateProgramPipeline(ids[num]); }

  void useProgramStages(shaderStage stages, GLuint program, int num = 0) const {
    glUseProgramStages(ids[num], static_cast<GLbitfield>(stages), program);
  }

  consteval int getNumberOfPipeline() const { return size; }

 private:
  std::array<GLuint, size> ids;
};