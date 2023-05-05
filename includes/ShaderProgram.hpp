#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <filesystem>
#include <string>
#include <unordered_map>

#include "enums.hpp"
#include "GLUtils.hpp"


class ShaderProgram {
public:
    static ShaderProgram fromGLSL(const std::filesystem::path &path, shaderType type);
    static ShaderProgram fromSPIRV(const std::filesystem::path &path, shaderType type);
    ~ShaderProgram();

    bool isValid() const { return m_id != 0;}

    explicit operator GLuint() const { return m_id; }
    shaderType getType() const;

    void getUniforms();
private:

    struct uniform_info
    {
        GLint location;
        GLsizei count;
    };

    std::unordered_map<std::string, uniform_info> uniforms;
    GLuint	m_id = 0;

    shaderType type;

    ShaderProgram(GLuint m_id, shaderType type): m_id(m_id), type(type) {}
};