#include "ShaderProgram.hpp"

#include <fmt/ranges.h>

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(m_id);
}

ShaderProgram ShaderProgram::fromGLSL(const std::filesystem::path &path, shaderType type) {
    const auto fileOpt = loadFile(path);

    if (!fileOpt){
        return  {0, type};
    }
    const std::string& file = *fileOpt;
    const char* source = file.c_str();

#if 1
    const GLuint id = glCreateShaderProgramv(static_cast<GLenum>(type), file.size(), &source);
#else
    const GLuint  id = 0;
#endif
    fmt::println("ss");

    if (id == 0){
        return {0, type};
    }

    if (!errorLink(id)) {
        return {0, type};
    }


    return {id, type};
}

ShaderProgram ShaderProgram::fromSPIRV(const std::filesystem::path &path, shaderType type) {
    const auto sourceOpt = loadBinary(path);

    if (!sourceOpt){
        return {0, type};
    }
    const std::vector<char> &source = *sourceOpt;

    const GLuint shader = glCreateShader(static_cast<GLenum>(type));

    glShaderBinary(1, &shader, GL_SHADER_BINARY_FORMAT_SPIR_V, source.data(), source.size());
    glSpecializeShader(shader, "main", 0, nullptr, nullptr);

    if (!errorShader(shader)){
        glDeleteShader(shader);
        return {0, type};
    }

    const GLuint program = glCreateProgram();

    if (program == 0){
        glDeleteShader(shader);
        return {0, type};
    }

    glProgramParameteri(program, GL_PROGRAM_SEPARABLE, GL_TRUE);

    glAttachShader(program, shader);

    glLinkProgram(program);

    if (!errorLink(program)){
        glDetachShader(program, shader);
        glDeleteShader(shader);
        glDeleteProgram(program);
        return {0, type};
    }

    glDetachShader(program, shader);
    glDeleteShader(shader);

    return {program, type};
}

void ShaderProgram::getUniforms() {
    GLint uniform_count = 0;
    glGetProgramiv(m_id, GL_ACTIVE_UNIFORMS, &uniform_count);

    if (uniform_count != 0)
    {
        fmt::println("{}", uniform_count);
        uniforms.reserve(uniform_count);

        GLint 	max_name_len = 0;
        GLsizei length = 0;
        GLsizei count = 0;
        GLenum 	type = GL_NONE;
        glGetProgramiv(m_id, GL_ACTIVE_UNIFORM_MAX_LENGTH, &max_name_len);

        auto uniform_name = std::make_unique<char[]>(max_name_len);

        for (GLint i = 0; i < uniform_count; ++i)
        {
            glGetActiveUniform(m_id, i, max_name_len, &length, &count, &type, uniform_name.get());

            uniform_info info;
            info.location = glGetUniformLocation(m_id, uniform_name.get());
            info.count = count;

            uniforms.emplace(std::string(uniform_name.get(), length), info);
        }

        fmt::println("Program id : {}", m_id);
        for(const auto& [key, value]: uniforms){
            fmt::println("{} -> {} {}", key, value.location, value.count);
        }
    }
}

shaderType ShaderProgram::getType() const {
    return type;
}


