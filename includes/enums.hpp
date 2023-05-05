#pragma once

#include <GL/glew.h>

enum class shaderType {
    COMPUTER = GL_COMPUTE_SHADER,
    VERTEX = GL_VERTEX_SHADER,
    TESS_CONTROL = GL_TESS_CONTROL_SHADER,
    TESS_EVALUATION = GL_TESS_EVALUATION_SHADER,
    GEOMETRY = GL_GEOMETRY_SHADER,
    FRAGMENT = GL_FRAGMENT_SHADER
};

enum class shaderStage : GLbitfield
{
    VERTEX = GL_VERTEX_SHADER_BIT,
    TESS_CONTROL = GL_TESS_CONTROL_SHADER_BIT,
    TESS_EVALUATION = GL_TESS_EVALUATION_SHADER_BIT,
    GEOMETRY = GL_GEOMETRY_SHADER_BIT,
    FRAGMENT = GL_FRAGMENT_SHADER_BIT,
    COMPUTE = GL_COMPUTE_SHADER_BIT,
    ALL_SHADER = GL_ALL_SHADER_BITS
};

inline shaderStage operator | (shaderStage lhs, shaderStage rhs)
{
    using T = std::underlying_type_t <shaderStage>;
    return static_cast<shaderStage>(static_cast<T>(lhs) | static_cast<T>(rhs));
}

inline shaderStage& operator |= (shaderStage& lhs, shaderStage rhs)
{
    lhs = lhs | rhs;
    return lhs;
}
