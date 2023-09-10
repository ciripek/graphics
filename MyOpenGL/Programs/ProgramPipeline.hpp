#pragma once

#include <GL/glew.h>

#include "enums.hpp"

class ProgramPipeline {
 public:
  ProgramPipeline();
  ~ProgramPipeline();

  DELETE_COPY(ProgramPipeline);

  ProgramPipeline(ProgramPipeline&& other) noexcept;
  ProgramPipeline& operator=(ProgramPipeline&& other) noexcept;

  void clean();

  void activeShaderProgram(GLuint program) const;
  void bind() const;
  static void unbind();
  void validate() const;
  void useProgramStages(shaderStage stages, GLuint program) const;

  operator GLuint();

 private:
  GLuint id = 0;
};
