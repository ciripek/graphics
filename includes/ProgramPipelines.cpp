#include "ProgramPipelines.hpp"

ProgramPipelines::ProgramPipelines(int num) : numberOfPipeline(num), ids(std::make_unique<GLuint[]>(num)) {
    glCreateProgramPipelines(numberOfPipeline, ids.get());
}

ProgramPipelines::~ProgramPipelines() {
    glDeleteProgramPipelines(numberOfPipeline, ids.get());
}

void ProgramPipelines::activeShaderProgram(GLuint program, int num) const{
    glActiveShaderProgram(ids[num], program);
}

void ProgramPipelines::validate(int num) const{
    glValidateProgramPipeline(ids[num]);
}

void ProgramPipelines::bind(int num) const{
    glBindProgramPipeline(ids[num]);
}

void ProgramPipelines::useProgramStages(shaderStage stages, GLuint program, int num) const {
    glUseProgramStages(ids[num], static_cast<GLbitfield>(stages), program);
}
