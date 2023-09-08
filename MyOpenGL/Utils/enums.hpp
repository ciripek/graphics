#pragma once

#include <GL/glew.h>

#include <type_traits>

#define DELETE_COPY(classname)          \
  classname(const classname&) = delete; \
  classname& operator=(const classname&) = delete;

#define DEFAULT_COPY(classname)          \
  classname(const classname&) = default; \
  classname& operator=(const classname&) = default;

#define DELETE_MOVE(classname)     \
  classname(classname&&) = delete; \
  classname& operator=(classname&&) = delete;

#define DEFAULT_MOVE(classname)     \
  classname(classname&&) = default; \
  classname& operator=(classname&&) = default;

enum class shaderType {
  COMPUTER = GL_COMPUTE_SHADER,
  VERTEX = GL_VERTEX_SHADER,
  TESS_CONTROL = GL_TESS_CONTROL_SHADER,
  TESS_EVALUATION = GL_TESS_EVALUATION_SHADER,
  GEOMETRY = GL_GEOMETRY_SHADER,
  FRAGMENT = GL_FRAGMENT_SHADER
};

enum class shaderStage : GLbitfield {
  VERTEX = GL_VERTEX_SHADER_BIT,
  TESS_CONTROL = GL_TESS_CONTROL_SHADER_BIT,
  TESS_EVALUATION = GL_TESS_EVALUATION_SHADER_BIT,
  GEOMETRY = GL_GEOMETRY_SHADER_BIT,
  FRAGMENT = GL_FRAGMENT_SHADER_BIT,
  COMPUTE = GL_COMPUTE_SHADER_BIT,
  ALL_SHADER = GL_ALL_SHADER_BITS
};

enum class textureType {
  Texture1D = GL_TEXTURE_1D,
  Texture2D = GL_TEXTURE_2D,
  Texture3D = GL_TEXTURE_3D,
  Texture1DArray = GL_TEXTURE_1D_ARRAY,
  Texture2DArray = GL_TEXTURE_2D_ARRAY,
  TextureRectangle = GL_TEXTURE_RECTANGLE,
  TextureCubeMap = GL_TEXTURE_CUBE_MAP,
  TextureCubeMapArray = GL_TEXTURE_CUBE_MAP_ARRAY,
  Texture2DMultisample = GL_TEXTURE_2D_MULTISAMPLE,
  Texture2DMultisampleArray = GL_TEXTURE_2D_MULTISAMPLE_ARRAY
};

enum class BufferType : GLenum {
  Array = GL_ARRAY_BUFFER,
  AtomicCounter = GL_ATOMIC_COUNTER_BUFFER,
  CopyRead = GL_COPY_READ_BUFFER,
  CopyWrite = GL_COPY_WRITE_BUFFER,
  DispatchIndirect = GL_DISPATCH_INDIRECT_BUFFER,
  DrawIndirect = GL_DRAW_INDIRECT_BUFFER,
  ElementArray = GL_ELEMENT_ARRAY_BUFFER,
  PixelPack = GL_PIXEL_PACK_BUFFER,
  PixelUnpack = GL_PIXEL_UNPACK_BUFFER,
  Query = GL_QUERY_BUFFER,
  ShaderStorage = GL_SHADER_STORAGE_BUFFER,
  Texture = GL_TEXTURE_BUFFER,
  TransformFeedback = GL_TRANSFORM_FEEDBACK_BUFFER,
  Uniform = GL_UNIFORM_BUFFER
};

enum class BufferUsage : GLenum {
  StreamDraw = GL_STREAM_DRAW,
  StreamRead = GL_STREAM_READ,
  StreamCopy = GL_STREAM_COPY,
  StaticDraw = GL_STATIC_DRAW,
  StaticRead = GL_STATIC_READ,
  StaticCopy = GL_STATIC_COPY,
  DynamicDraw = GL_DYNAMIC_DRAW,
  DynamicRead = GL_DYNAMIC_READ,
  DynamicCopy = GL_DYNAMIC_COPY
};

enum class BufferStorageUsage : GLbitfield {
  Zero = 0,
  DynamicStorageBit = GL_DYNAMIC_STORAGE_BIT,
  MapReadBit = GL_MAP_READ_BIT,
  MapWriteBit = GL_MAP_WRITE_BIT,
  MapPersistentBit = GL_MAP_PERSISTENT_BIT,
  MapCoherentBit = GL_MAP_COHERENT_BIT,
  ClientStorageBit = GL_CLIENT_STORAGE_BIT
};

#define ENUM_CLASS_OR(type)                                              \
  constexpr inline type operator|(type lhs, type rhs) {                  \
    using T = std::underlying_type_t<type>;                              \
    return static_cast<type>(static_cast<T>(lhs) | static_cast<T>(rhs)); \
  }                                                                      \
  constexpr inline type& operator|=(type& lhs, type rhs) {               \
    lhs = lhs | rhs;                                                     \
    return lhs;                                                          \
  }

#define ENUM_CLASS_AND(type)                                             \
  constexpr inline type operator&(type lhs, type rhs) {                  \
    using T = std::underlying_type_t<type>;                              \
    return static_cast<type>(static_cast<T>(lhs) & static_cast<T>(rhs)); \
  }                                                                      \
  constexpr inline type& operator&=(type& lhs, type rhs) {               \
    lhs = lhs & rhs;                                                     \
    return lhs;                                                          \
  }

ENUM_CLASS_OR(shaderStage)
ENUM_CLASS_AND(shaderStage)

ENUM_CLASS_OR(BufferStorageUsage)
ENUM_CLASS_AND(BufferStorageUsage)

inline constexpr bool isBitSet(BufferStorageUsage bitfield,
                               BufferStorageUsage bit) {
  return static_cast<GLbitfield>(bitfield & bit) != 0U;
}