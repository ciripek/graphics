#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <filesystem>
#include <span>
#include <string>
#include <string_view>
#include <unordered_map>

#include "enums.hpp"
#include "GLUtils.hpp"


class ShaderProgram {
public:
    static ShaderProgram fromGLSL(const std::filesystem::path &path, shaderType type);
    static ShaderProgram fromGLSL(const std::filesystem::path &path){
        return fromGLSL(path, getTypeFromFile(path));
    }

    static ShaderProgram fromSPIRV(const std::filesystem::path &path, shaderType type);
    static ShaderProgram fromSPIRV(const std::filesystem::path &path){
        return fromSPIRV(path, getTypeFromFile(path));
    }

    ~ShaderProgram();

    bool isValid() const { return m_id != 0;}

    operator GLuint() const { return m_id; }
    shaderType getType() const;

    void cacheUniforms();

    void setUniform(const std::string&, std::span<GLfloat>, int = 0);
    void setUniform(const std::string&, std::span<glm::vec2>, int = 0);
    void setUniform(const std::string&, std::span<glm::vec3>, int = 0);
    void setUniform(const std::string&, std::span<glm::vec4>, int = 0);

    void setUniform(const std::string&, std::span<GLint>, int = 0);
    void setUniform(const std::string&, std::span<glm::ivec2>, int = 0);
    void setUniform(const std::string&, std::span<glm::ivec3>, int = 0);
    void setUniform(const std::string&, std::span<glm::ivec4>, int = 0);

    void setUniform(const std::string&, std::span<GLuint>, int = 0);
    void setUniform(const std::string&, std::span<glm::uvec2>, int = 0);
    void setUniform(const std::string&, std::span<glm::uvec3>, int = 0);
    void setUniform(const std::string&, std::span<glm::uvec4>, int = 0);


    void setUniform(const std::string &name, std::span<glm::mat2> value, GLboolean transpose = GL_FALSE, int begin = 0);
    void setUniform(const std::string &name, std::span<glm::dmat2> value, GLboolean transpose = GL_FALSE, int begin = 0);
    void setUniform(const std::string &name, std::span<glm::mat3> value, GLboolean transpose = GL_FALSE, int begin = 0);
    void setUniform(const std::string &name, std::span<glm::dmat3> value, GLboolean transpose = GL_FALSE, int begin = 0);
    void setUniform(const std::string &name, std::span<glm::mat4> value, GLboolean transpose = GL_FALSE, int begin = 0);
    void setUniform(const std::string &name, std::span<glm::dmat4> value, GLboolean transpose = GL_FALSE, int begin = 0);

    void setUniform(const std::string &name, const glm::mat2 &value, GLboolean transpose = GL_FALSE);
    void setUniform(const std::string &name, const glm::dmat2 &value, GLboolean transpose = GL_FALSE);
    void setUniform(const std::string &name, const glm::mat3 &value, GLboolean transpose = GL_FALSE);
    void setUniform(const std::string &name, const glm::dmat3 &value, GLboolean transpose = GL_FALSE);
    void setUniform(const std::string &name, const glm::mat4 &value, GLboolean transpose = GL_FALSE);
    void setUniform(const std::string &name, const glm::dmat4 &value, GLboolean transpose = GL_FALSE);

    void setUniform(const std::string&, GLfloat);
    void setUniform(const std::string&, glm::vec1 vec);

    void setUniform(const std::string&, GLfloat, GLfloat);
    void setUniform(const std::string&, glm::vec2);

    void setUniform(const std::string&, GLfloat, GLfloat, GLfloat);
    void setUniform(const std::string&, glm::vec3);

    void setUniform(const std::string&, GLfloat, GLfloat, GLfloat, GLfloat);
    void setUniform(const std::string&, glm::vec4);

    void setUniform(const std::string&, GLint);
    void setUniform(const std::string&, glm::ivec1);

    void setUniform(const std::string&, GLint, GLint);
    void setUniform(const std::string&, glm::ivec2);

    void setUniform(const std::string&, GLint, GLint, GLint);
    void setUniform(const std::string&, glm::ivec3);

    void setUniform(const std::string&, GLint, GLint, GLint ,GLint );
    void setUniform(const std::string&, glm::ivec4);

    void setUniform(const std::string&, GLuint);
    void setUniform(const std::string&, glm::uvec1);

    void setUniform(const std::string&, GLuint, GLuint);
    void setUniform(const std::string&, glm::uvec2);

    void setUniform(const std::string&, GLuint, GLuint, GLuint);
    void setUniform(const std::string&, glm::uvec3);

    void setUniform(const std::string&, GLuint, GLuint, GLuint,GLuint );
    void setUniform(const std::string&, glm::uvec4);

    GLsizei getUniformCount(const std::string &name){
        return uniforms[name].count;
    }

    void setTexture(const std::string &uniform, GLint sampler, GLuint textureID);
private:

    struct uniform_info
    {
        GLint location;
        GLsizei count;
    };

    std::unordered_map<std::string, uniform_info> uniforms;

    GLint get(const std::string & key , int begin = 0) {
        const auto it = uniforms.find( key );

        if ( it == uniforms.end() ) {
            return -1;
        }

        return it->second.location + begin;
    }

    GLuint	m_id = 0;

    shaderType type;

    ShaderProgram(GLuint m_id, shaderType type): m_id(m_id), type(type) {}
    static shaderType getTypeFromFile(const std::filesystem::path &path);
};