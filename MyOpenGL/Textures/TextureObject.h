#pragma once

#include <GL/glew.h>

#include <string>

#include "enums.hpp"

template <textureType type = textureType::Texture2D>
class TextureObject final {
 public:
  TextureObject();
  TextureObject(const std::string&);
  ~TextureObject();

  TextureObject(const TextureObject&) = delete;
  TextureObject& operator=(const TextureObject&) = delete;

  TextureObject(TextureObject&& rhs);
  TextureObject& operator=(TextureObject&& rhs);

  TextureObject& operator=(const std::string& s);

  void AttachFromFile(const std::string&,
                      bool generateMipMap = true,
                      GLuint role = static_cast<GLuint>(type));
  void FromFile(const std::string&);

  operator unsigned int() const { return m_id; }

  void Clean();

 private:
  GLuint m_id{};
};

#include "TextureObject.inl"

using Texture2D = TextureObject<>;
using TextureCubeMap = TextureObject<textureType::TextureCubeMap>;