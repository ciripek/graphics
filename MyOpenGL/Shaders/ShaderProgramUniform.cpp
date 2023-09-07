#include "ShaderProgram.hpp"

#include <glm/gtc/type_ptr.hpp>

void ShaderProgram::setUniform(const std::string& name,
                               std::span<GLfloat> value,
                               int begin) {
  glProgramUniform1fv(m_id, get(name, begin), value.size(), value.data());
}

void ShaderProgram::setUniform(const std::string& name,
                               std::span<glm::vec2> value,
                               int begin) {
  glProgramUniform2fv(m_id, get(name, begin), value.size(),
                      glm::value_ptr(value.front()));
}

void ShaderProgram::setUniform(const std::string& name,
                               std::span<glm::vec3> value,
                               int begin) {
  glProgramUniform3fv(m_id, get(name, begin), value.size(),
                      glm::value_ptr(value.front()));
}

void ShaderProgram::setUniform(const std::string& name,
                               std::span<glm::vec4> value,
                               int begin) {
  glProgramUniform4fv(m_id, get(name, begin), value.size(),
                      glm::value_ptr(value.front()));
}

void ShaderProgram::setUniform(const std::string& name,
                               std::span<GLuint> value,
                               int begin) {
  glProgramUniform1uiv(m_id, get(name, begin), value.size(), value.data());
}

void ShaderProgram::setUniform(const std::string& name,
                               std::span<glm::uvec2> value,
                               int begin) {
  glProgramUniform2uiv(m_id, get(name), value.size(),
                       glm::value_ptr(value.front()));
}

void ShaderProgram::setUniform(const std::string& name,
                               std::span<glm::uvec3> value,
                               int begin) {
  glProgramUniform3uiv(m_id, get(name, begin), value.size(),
                       glm::value_ptr(value.front()));
}

void ShaderProgram::setUniform(const std::string& name,
                               std::span<glm::uvec4> value,
                               int begin) {
  glProgramUniform4uiv(m_id, get(name, begin), value.size(),
                       glm::value_ptr(value.front()));
}

void ShaderProgram::setUniform(const std::string& name, GLfloat v1) {
  glProgramUniform1f(m_id, get(name), v1);
}

void ShaderProgram::setUniform(const std::string& name, glm::vec1 vec) {
  setUniform(name, vec.x);
}

void ShaderProgram::setUniform(const std::string& name,
                               GLfloat v0,
                               GLfloat v1) {
  glProgramUniform2f(m_id, get(name), v0, v1);
}

void ShaderProgram::setUniform(const std::string& name, glm::vec2 vec) {
  setUniform(name, vec.x, vec.y);
}

void ShaderProgram::setUniform(const std::string& name,
                               GLfloat v0,
                               GLfloat v1,
                               GLfloat v2) {
  glProgramUniform3f(m_id, get(name), v0, v1, v2);
}

void ShaderProgram::setUniform(const std::string& name, glm::vec3 vec) {
  setUniform(name, vec.x, vec.y, vec.z);
}

void ShaderProgram::setUniform(const std::string& name,
                               GLfloat v0,
                               GLfloat v1,
                               GLfloat v2,
                               GLfloat v3) {
  glProgramUniform4f(m_id, get(name), v0, v1, v2, v3);
}

void ShaderProgram::setUniform(const std::string& name, glm::vec4 vec) {
  setUniform(name, vec.x, vec.y, vec.z, vec.w);
}

void ShaderProgram::setUniform(const std::string& name,
                               std::span<GLint> value,
                               int begin) {
  glProgramUniform1iv(m_id, get(name), value.size(), value.data());
}

void ShaderProgram::setUniform(const std::string& name, GLint v0) {
  glProgramUniform1i(m_id, get(name), v0);
}

void ShaderProgram::setUniform(const std::string& name, glm::ivec1 vec) {
  setUniform(name, vec.x);
}

void ShaderProgram::setUniform(const std::string& name,
                               std::span<glm::ivec2> value,
                               int begin) {
  glProgramUniform2iv(m_id, get(name, begin), value.size(),
                      glm::value_ptr(value.front()));
}

void ShaderProgram::setUniform(const std::string& name, GLint v0, GLint v1) {
  glProgramUniform2i(m_id, get(name), v0, v1);
}

void ShaderProgram::setUniform(const std::string& name, glm::ivec2 vec) {
  setUniform(name, vec.x, vec.y);
}

void ShaderProgram::setUniform(const std::string& name,
                               std::span<glm::ivec3> value,
                               int begin) {
  glProgramUniform3iv(m_id, get(name, begin), value.size(),
                      glm::value_ptr(value.front()));
}

void ShaderProgram::setUniform(const std::string& name,
                               GLint v0,
                               GLint v1,
                               GLint v2) {
  glProgramUniform3i(m_id, get(name), v0, v1, v2);
}

void ShaderProgram::setUniform(const std::string& name, glm::ivec3 vec) {
  setUniform(name, vec.x, vec.x, vec.z);
}

void ShaderProgram::setUniform(const std::string& name,
                               std::span<glm::ivec4> value,
                               int begin) {
  glProgramUniform4iv(m_id, get(name, begin), value.size(),
                      glm::value_ptr(value.front()));
}

void ShaderProgram::setUniform(const std::string& name,
                               GLint v0,
                               GLint v1,
                               GLint v2,
                               GLint v3) {
  glProgramUniform4i(m_id, get(name), v0, v1, v2, v3);
}

void ShaderProgram::setUniform(const std::string& name, glm::ivec4 vec) {
  setUniform(name, vec.x, vec.y, vec.z, vec.w);
}

void ShaderProgram::setUniform(const std::string& name, GLuint v0) {
  glProgramUniform1ui(m_id, get(name), v0);
}

void ShaderProgram::setUniform(const std::string& name, glm::uvec1 vec) {
  setUniform(name, vec.x);
}

void ShaderProgram::setUniform(const std::string& name, GLuint v0, GLuint v1) {
  glProgramUniform2ui(m_id, get(name), v0, v1);
}

void ShaderProgram::setUniform(const std::string& name, glm::uvec2 vec) {
  setUniform(name, vec.x, vec.y);
}

void ShaderProgram::setUniform(const std::string& name,
                               GLuint v0,
                               GLuint v1,
                               GLuint v2) {
  glProgramUniform3ui(m_id, get(name), v0, v1, v2);
}

void ShaderProgram::setUniform(const std::string& name, glm::uvec3 vec) {
  setUniform(name, vec.x, vec.x, vec.z);
}

void ShaderProgram::setUniform(const std::string& name,
                               GLuint v0,
                               GLuint v1,
                               GLuint v2,
                               GLuint v3) {
  glProgramUniform4ui(m_id, get(name), v0, v1, v2, v3);
}

void ShaderProgram::setUniform(const std::string& name, glm::uvec4 vec) {
  setUniform(name, vec.x, vec.y, vec.z, vec.w);
}

void ShaderProgram::setUniform(const std::string& name,
                               std::span<glm::mat2> value,
                               GLboolean transpose,
                               int begin) {
  glProgramUniformMatrix2fv(m_id, get(name, begin), value.size(), transpose,
                            glm::value_ptr(value.front()));
}

void ShaderProgram::setUniform(const std::string& name,
                               std::span<glm::dmat2> value,
                               GLboolean transpose,
                               int begin) {
  glProgramUniformMatrix2dv(m_id, get(name, begin), value.size(), transpose,
                            glm::value_ptr(value.front()));
}

void ShaderProgram::setUniform(const std::string& name,
                               std::span<glm::mat3> value,
                               GLboolean transpose,
                               int begin) {
  glProgramUniformMatrix3fv(m_id, get(name, begin), value.size(), transpose,
                            glm::value_ptr(value.front()));
}

void ShaderProgram::setUniform(const std::string& name,
                               std::span<glm::dmat3> value,
                               GLboolean transpose,
                               int begin) {
  glProgramUniformMatrix3dv(m_id, get(name, begin), value.size(), transpose,
                            glm::value_ptr(value.front()));
}

void ShaderProgram::setUniform(const std::string& name,
                               std::span<glm::mat4> value,
                               GLboolean transpose,
                               int begin) {
  glProgramUniformMatrix4fv(m_id, uniforms[name].location + begin, value.size(),
                            transpose, glm::value_ptr(value.front()));
}

void ShaderProgram::setUniform(const std::string& name,
                               std::span<glm::dmat4> value,
                               GLboolean transpose,
                               int begin) {
  glProgramUniformMatrix4dv(m_id, uniforms[name].location + begin, value.size(),
                            transpose, glm::value_ptr(value.front()));
}

void ShaderProgram::setUniform(const std::string& name,
                               const glm::mat2& value,
                               GLboolean transpose) {
  glProgramUniformMatrix2fv(m_id, uniforms[name].location, 1, transpose,
                            glm::value_ptr(value));
}

void ShaderProgram::setUniform(const std::string& name,
                               const glm::mat3& value,
                               GLboolean transpose) {
  glProgramUniformMatrix3fv(m_id, uniforms[name].location, 1, transpose,
                            glm::value_ptr(value));
}

void ShaderProgram::setUniform(const std::string& name,
                               const glm::mat4& value,
                               GLboolean transpose) {
  glProgramUniformMatrix4fv(m_id, uniforms[name].location, 1, transpose,
                            glm::value_ptr(value));
}

void ShaderProgram::setUniform(const std::string& name,
                               const glm::dmat2& value,
                               GLboolean transpose) {
  glProgramUniformMatrix2dv(m_id, uniforms[name].location, 1, transpose,
                            glm::value_ptr(value));
}

void ShaderProgram::setUniform(const std::string& name,
                               const glm::dmat3& value,
                               GLboolean transpose) {
  glProgramUniformMatrix3dv(m_id, uniforms[name].location, 1, transpose,
                            glm::value_ptr(value));
}

void ShaderProgram::setUniform(const std::string& name,
                               const glm::dmat4& value,
                               GLboolean transpose) {
  glProgramUniformMatrix4dv(m_id, uniforms[name].location, 1, transpose,
                            glm::value_ptr(value));
}
