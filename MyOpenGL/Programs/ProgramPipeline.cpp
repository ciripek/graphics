#include "ProgramPipeline.hpp"

#include <utility>

ProgramPipeline::ProgramPipeline() {
  glCreateProgramPipelines(1, &id);
}

ProgramPipeline::~ProgramPipeline() {
  clean();
}

void ProgramPipeline::clean() {
  if (id != 0U) {
    glDeleteProgramPipelines(1, &id);
    id = 0;
  }
}
ProgramPipeline::ProgramPipeline(ProgramPipeline&& other) noexcept
    : id(std::exchange(other.id, 0)) {}

ProgramPipeline& ProgramPipeline::operator=(ProgramPipeline&& other) noexcept {
  if (this != &other) {
    clean();

    id = std::exchange(other.id, 0);
  }

  return *this;
}

void ProgramPipeline::activeShaderProgram(GLuint program) const {
  glActiveShaderProgram(id, program);
}

void ProgramPipeline::bind() const {
  glBindProgramPipeline(id);
}

void ProgramPipeline::unbind() {
  glBindProgramPipeline(0);
}

void ProgramPipeline::validate() const {
  glValidateProgramPipeline(id);
}
void ProgramPipeline::useProgramStages(shaderStage stages,
                                       GLuint program) const {
  glUseProgramStages(id, static_cast<GLbitfield>(stages), program);
}

ProgramPipeline::operator GLuint() {
  return id;
}
