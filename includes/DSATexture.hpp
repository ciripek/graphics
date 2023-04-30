#pragma once

#include <GL/glew.h>
#include <string>

enum class DSATextureType
{
    Texture1D					= GL_TEXTURE_1D,
    Texture2D					= GL_TEXTURE_2D,
    Texture3D					= GL_TEXTURE_3D,
    Texture1DArray				= GL_TEXTURE_1D_ARRAY,
    Texture2DArray				= GL_TEXTURE_2D_ARRAY,
    TextureRectangle			= GL_TEXTURE_RECTANGLE,
    TextureCubeMap				= GL_TEXTURE_CUBE_MAP,
    TextureCubeMapArray			= GL_TEXTURE_CUBE_MAP_ARRAY,
    Texture2DMultisample		= GL_TEXTURE_2D_MULTISAMPLE,
    Texture2DMultisampleArray	= GL_TEXTURE_2D_MULTISAMPLE_ARRAY
};

class DSATexture {
public:
    explicit DSATexture(DSATextureType type = DSATextureType::Texture2D);

    explicit DSATexture(const std::string&name, DSATextureType type = DSATextureType::Texture2D);
    ~DSATexture();

    DSATexture(const DSATexture&) = delete;
    DSATexture& operator=(const DSATexture&) = delete;

    DSATexture(DSATexture&& rhs) noexcept  = default;
    DSATexture& operator=(DSATexture&& rhs) noexcept = default;

    DSATexture& operator=(const std::string& name);

    void AttachFromFile(const std::string&, bool generateMipMap = true);
    void FromFile(const std::string&);

    explicit operator unsigned int() const { return m_id; }

    void Clean();
private:
    GLuint m_id{};
};