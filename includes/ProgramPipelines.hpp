#pragma once

#include <GL/glew.h>

#include <memory>

#include "enums.hpp"

class ProgramPipelines {
public:
    explicit ProgramPipelines(int num = 1);
    ~ProgramPipelines();

    ProgramPipelines (const ProgramPipelines & ) = delete;
    ProgramPipelines & operator= (const ProgramPipelines & ) = delete;
    ProgramPipelines (ProgramPipelines && ) noexcept = default;
    ProgramPipelines& operator=(ProgramPipelines&&) noexcept = default;

    void activeShaderProgram(GLuint program, int num = 0) const;

    void bind(int num = 0) const ;
    void validate(int num = 0) const;
    void useProgramStages(shaderStage stages, GLuint program, int num = 0) const;
private:
    int numberOfPipeline;
    std::unique_ptr<GLuint[]> ids;
};