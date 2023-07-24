#pragma once

#include <GL/glew.h>

#define DELETE_COPY(classname)  \
    classname ( const classname & ) = delete; \
    classname & operator= ( const classname & ) = delete;

#define DEFAULT_COPY(classname)  \
    classname ( const classname & ) = default; \
    classname & operator= ( const classname & ) = default;

#define DELETE_MOVE(classname) \
    classname ( classname && ) = delete; \
    classname& operator=(classname&&) = delete;


#define DEFAULT_MOVE(classname) \
    classname ( classname && ) = default; \
    classname& operator=(classname&&) = default;


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

enum class textureType
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
