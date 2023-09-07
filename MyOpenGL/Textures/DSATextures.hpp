#pragma once

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_image.h>

#include <filesystem>
#include <memory>
#include <string>
#include <utility>

#include "GLUtils.hpp"
#include "enums.hpp"
#include "spdlog-config.hpp"

template <textureType type = textureType::Texture2D>
class DSATextures {
 public:
  DSATextures() = default;

  explicit DSATextures(int size)
      : size(size), ids(std::make_unique<GLuint[]>(size)) {
    glCreateTextures(static_cast<GLenum>(type), size, ids.get());
  }

  ~DSATextures() {
    if (ids != nullptr) {
      glDeleteTextures(size, ids.get());
    }
  }

  DSATextures(const DSATextures&) = delete;
  DSATextures& operator=(const DSATextures&) = delete;

  DSATextures(DSATextures&& rhs) noexcept = default;
  DSATextures& operator=(DSATextures&& rhs) noexcept = default;

  constexpr GLuint& operator[](std::size_t i) { return ids[i]; }

  void AttachFromFile(const std::filesystem::path& name,
                      bool generateMipMap = true,
                      int index = 0) {
    SDL_Surface* loaded_img = IMG_Load(name.c_str());

    if (loaded_img == nullptr) {
      SPDLOG_ERROR("[AttachFromFile] Error loading image file {}",
                   name.native());
      return;
    }

    // Formátum meghatározása és szükség esetén konvertálás
    const Uint32 sdl_format = loaded_img->format->BytesPerPixel == 3
                                  ? SDL_PIXELFORMAT_RGB24
                                  : SDL_PIXELFORMAT_RGBA32;
    GLenum source_format =
        loaded_img->format->BytesPerPixel == 3 ? GL_RGB : GL_RGBA;
    GLenum source = loaded_img->format->BytesPerPixel == 3 ? GL_RGB8 : GL_RGBA8;

    if (loaded_img->format->format != sdl_format) {
      SDL_Surface* formattedSurf =
          SDL_ConvertSurfaceFormat(loaded_img, sdl_format, 0);
      SDL_FreeSurface(loaded_img);
      if (formattedSurf == nullptr) {
        const char* message = SDL_GetError();
        SPDLOG_ERROR("[AttachFromFile] Error converting image format: {}",
                     message);
        return;
      }
      loaded_img = formattedSurf;
    }

    // Áttérés SDL koordinátarendszerről ( (0,0) balfent ) OpenGL
    // textúra-koordinátarendszerre ( (0,0) ballent )
    if constexpr (type != textureType::TextureCubeMap &&
                  type != textureType::TextureCubeMapArray) {
      if (invert_image(loaded_img->pitch, loaded_img->h, loaded_img->pixels) ==
          -1) {
        const char* message = SDL_GetError();

        SPDLOG_ERROR("[AttachFromFile] Error transforming image: {}", message);
        SDL_FreeSurface(loaded_img);
        return;
      }
    }

    glTextureStorage2D(ids[index], 1, source, loaded_img->w, loaded_img->h);
    glTextureSubImage2D(ids[index], 0, 0, 0, loaded_img->w, loaded_img->h,
                        source_format, GL_UNSIGNED_BYTE, loaded_img->pixels);

    if (generateMipMap)
      glGenerateTextureMipmap(ids[index]);

    glTextureParameteri(ids[index], GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(ids[index], GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    SDL_FreeSurface(loaded_img);
  }

 private:
  std::unique_ptr<GLuint[]> ids;
  int size = 0;
};

using DSATexture2D = DSATextures<textureType::Texture2D>;