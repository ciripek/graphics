#pragma once

#include <GL/glew.h>

#include <filesystem>
#include <string>
#include <utility>

#include "GLconversions.hpp"

class ShaderObject final {
 public:
  explicit ShaderObject(GLenum pType);
  ShaderObject(GLenum pType, const std::string&);
  explicit ShaderObject(const TypeSourcePair& pInfo)
      : ShaderObject(pInfo.first, pInfo.second) {}

  ~ShaderObject();

  ShaderObject(const ShaderObject&) = delete;
  ShaderObject& operator=(const ShaderObject&) = delete;

  ShaderObject(ShaderObject&&);
  ShaderObject& operator=(ShaderObject&&);

  operator unsigned int() const { return m_id; }

  bool FromFile(const std::filesystem::path& fileName) const;
  bool FromMemory(const std::string& _source) const;

 private:
  static GLuint CompileShaderFromMemory(GLuint _shaderObject,
                                        const std::string& _source);

  GLuint m_id;
};