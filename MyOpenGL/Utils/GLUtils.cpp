#include "GLUtils.hpp"

#include <SDL_image.h>

#include <fstream>
#include <memory>

#include "spdlog-config.hpp"

std::optional<std::string> loadFile(const std::filesystem::path& fileName) {
  std::ifstream shaderStream(fileName);
  if (!shaderStream.is_open()) {
    SPDLOG_ERROR("Error while loading shader {}!", fileName.native());
    return std::nullopt;
  }

  auto filesize = std::filesystem::file_size(fileName);

  std::string shaderCode(filesize, '\0');
  shaderStream.read(shaderCode.data(), filesize);

  shaderStream.close();

  return shaderCode;
}

GLuint loadShader(GLenum _shaderType, const std::filesystem::path& fileName) {
  // shader azonosito letrehozasa
  const GLuint loadedShader = glCreateShader(_shaderType);

  // ha nem sikerult hibauzenet es -1 visszaadasa
  if (loadedShader == 0) {
    SPDLOG_ERROR("Error while initing shader {} (glCreateShader)!",
                 fileName.native());
    return 0;
  }

  auto file = loadFile(fileName);
  if (!file) {
    SPDLOG_ERROR("Error while loading shader {}!", fileName.native());
    return 0;
  }

  // fajlbol betoltott kod hozzarendelese a shader-hez
  const char* sourcePointer = file->c_str();
  glShaderSource(loadedShader, 1, &sourcePointer, nullptr);

  // shader leforditasa
  glCompileShader(loadedShader);

  // ellenorizzuk, h minden rendben van-e
  if (errorShader(loadedShader)) {
    return 0;
  }

  return loadedShader;
}

GLuint loadProgramVSGSFS(const std::filesystem::path& _fileNameVS,
                         const std::filesystem::path& _fileNameGS,
                         const std::filesystem::path& _fileNameFS) {
  // a vertex, geometry es fragment shaderek betoltese
  const GLuint vs_ID = loadShader(GL_VERTEX_SHADER, _fileNameVS);
  const GLuint gs_ID = loadShader(GL_GEOMETRY_SHADER, _fileNameGS);
  const GLuint fs_ID = loadShader(GL_FRAGMENT_SHADER, _fileNameFS);

  // ha barmelyikkel gond volt programot sem tudunk csinalni, 0 vissza
  if (vs_ID == 0 || gs_ID == 0 || fs_ID == 0) {
    return 0;
  }

  // linkeljuk ossze a dolgokat
  const GLuint program_ID = glCreateProgram();

  SPDLOG_INFO("Linking program");
  glAttachShader(program_ID, vs_ID);
  glAttachShader(program_ID, gs_ID);
  glAttachShader(program_ID, fs_ID);

  glLinkProgram(program_ID);

  // linkeles ellenorzese
  GLint infoLogLength = 0, result = 0;

  glGetProgramiv(program_ID, GL_LINK_STATUS, &result);
  glGetProgramiv(program_ID, GL_INFO_LOG_LENGTH, &infoLogLength);
  if (GL_FALSE == result) {
    char* programErrorMessage = new char[infoLogLength];
    glGetProgramInfoLog(program_ID, infoLogLength, nullptr,
                        programErrorMessage);
    SPDLOG_ERROR("{}", programErrorMessage);
  }

  // mar nincs ezekre szukseg
  glDeleteShader(vs_ID);
  glDeleteShader(gs_ID);
  glDeleteShader(fs_ID);

  // adjuk vissza a program azonositojat
  return program_ID;
}

int invert_image(int pitch, int height, void* image_pixels) {
  int index;
  void* temp_row;
  int height_div_2;

  temp_row = (void*)malloc(pitch);
  if (NULL == temp_row) {
    SDL_SetError("Not enough memory for image inversion");
    return -1;
  }
  // if height is odd, don't need to swap middle row
  height_div_2 = (int)(height * .5);
  for (index = 0; index < height_div_2; index++) {
    // uses string.h
    memcpy((Uint8*)temp_row, (Uint8*)(image_pixels) + pitch * index, pitch);

    memcpy((Uint8*)(image_pixels) + pitch * index,
           (Uint8*)(image_pixels) + pitch * (height - index - 1), pitch);
    memcpy((Uint8*)(image_pixels) + pitch * (height - index - 1), temp_row,
           pitch);
  }
  free(temp_row);
  return 0;
}

int SDL_InvertSurface(SDL_Surface* image) {
  if (nullptr == image) {
    SDL_SetError("Surface is NULL");
    return -1;
  }

  return invert_image(image->pitch, image->h, image->pixels);
}

GLuint TextureFromFile(const char* filename) {
  // Kép betöltése
  SDL_Surface* loaded_img = IMG_Load(filename);
  if (loaded_img == nullptr) {
    SPDLOG_ERROR("[TextureFromFile] Error while loading texture: {}", filename);
    return 0;
  }

  // Uint32-ben tárolja az SDL a színeket, ezért számít a bájtsorrend
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
  const Uint32 format = SDL_PIXELFORMAT_ABGR8888;
#else
  const Uint32 format = SDL_PIXELFORMAT_RGBA8888;
#endif

  // Átalakítás 32bit RGBA formátumra, ha nem abban volt
  SDL_Surface* formattedSurf = SDL_ConvertSurfaceFormat(loaded_img, format, 0);
  if (formattedSurf == nullptr) {
    const char* message = SDL_GetError();
    SPDLOG_ERROR("[TextureFromFile] Error while processing texture: {}",
                 message);
    SDL_FreeSurface(loaded_img);
    return 0;
  }

  // Áttérés SDL koordinátarendszerről ( (0,0) balfent ) OpenGL
  // textúra-koordinátarendszerre ( (0,0) ballent )
  if (SDL_InvertSurface(formattedSurf) == -1) {
    const char* message = SDL_GetError();

    SPDLOG_ERROR("[TextureFromFile] Error while processing texture: {}",
                 message);
    SDL_FreeSurface(formattedSurf);
    SDL_FreeSurface(loaded_img);
    return 0;
  }

  // OpenGL textúra generálás
  GLuint tex;
  glGenTextures(1, &tex);

  glBindTexture(GL_TEXTURE_2D, tex);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, formattedSurf->w, formattedSurf->h, 0,
               GL_RGBA, GL_UNSIGNED_BYTE, formattedSurf->pixels);

  // Mipmap generálása
  glGenerateMipmap(GL_TEXTURE_2D);

  glBindTexture(GL_TEXTURE_2D, 0);

  // Használt SDL_Surface-k felszabadítása
  SDL_FreeSurface(formattedSurf);
  SDL_FreeSurface(loaded_img);

  return tex;
}

void TextureFromFileAttach(const char* filename, GLuint role) {
  SDL_Surface* loaded_img = IMG_Load(filename);

  int img_mode = 0;

  if (loaded_img == nullptr) {
    SPDLOG_ERROR("[TextureFromFile] Error while loading texture: {}", filename);
    return;
  }

#if SDL_BYTEORDER == SDL_LIL_ENDIAN
  if (loaded_img->format->BytesPerPixel == 4) {
    img_mode = GL_BGRA;
  } else {
    img_mode = GL_BGR;
  }
#else
  if (loaded_img->format->BytesPerPixel == 4) {
    img_mode = GL_RGBA;
  } else {
    img_mode = GL_RGB;
  }
#endif

  glTexImage2D(role, 0, GL_RGBA, loaded_img->w, loaded_img->h, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, loaded_img->pixels);

  SDL_FreeSurface(loaded_img);
}

GLuint genSampler(GLint param_min, GLint param_mag) {
  GLuint samp;
  glGenSamplers(1, &samp);

  glSamplerParameteri(samp, GL_TEXTURE_MIN_FILTER, param_min);
  glSamplerParameteri(samp, GL_TEXTURE_MAG_FILTER, param_mag);

  return samp;
}

std::optional<std::vector<char>> loadBinary(
    const std::filesystem::path& fileName) {
  std::ifstream shaderStream(fileName, std::ios_base::binary);

  if (!shaderStream.is_open()) {
    SPDLOG_ERROR("Error while loading binary shader {}!", fileName.native());
    return std::nullopt;
  }

  auto filesize = std::filesystem::file_size(fileName);

  std::vector<char> shaderCode(filesize);
  shaderStream.read(shaderCode.data(), filesize);

  shaderStream.close();

  return shaderCode;
}

bool errorShader(const GLuint loadedShader) {
  GLint result = GL_FALSE;

  // forditas statuszanak lekerdezese
  glGetShaderiv(loadedShader, GL_COMPILE_STATUS, &result);

  if (GL_FALSE == result) {
    // hibauzenet elkerese es kiirasa

    GLint infoLogLength = 0;
    glGetShaderiv(loadedShader, GL_INFO_LOG_LENGTH, &infoLogLength);

    char* errorMessage = new char[infoLogLength];
    glGetShaderInfoLog(loadedShader, infoLogLength, nullptr, errorMessage);

    SPDLOG_ERROR("Shader error: {}", errorMessage);

    delete[] errorMessage;
    return false;
  }

  return true;
}

bool errorLink(GLuint program) {
  GLint isLinked = GL_TRUE;

  // forditas statuszanak lekerdezese
  glGetProgramiv(program, GL_LINK_STATUS, &isLinked);

  if (isLinked == GL_FALSE) {
    // hibauzenet elkerese es kiirasa

    GLint infoLogLength = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

    char* errorMessage = new char[infoLogLength];
    glGetProgramInfoLog(program, infoLogLength, nullptr, errorMessage);

    SPDLOG_ERROR("Linker error: {}\n{}", infoLogLength, errorMessage);

    delete[] errorMessage;
    return false;
  }

  return true;
}
