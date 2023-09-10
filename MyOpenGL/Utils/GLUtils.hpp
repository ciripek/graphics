﻿#pragma once

#include <GL/glew.h>

#include <SDL.h>

#include <filesystem>
#include <optional>
#include <vector>
std::optional<std::string> loadFile(const std::filesystem::path& fileName);
std::optional<std::vector<char>> loadBinary(
    const std::filesystem::path& fileName);

GLuint loadShader(GLenum _shaderType, const std::filesystem::path& fileName);
GLuint loadProgramVSGSFS(const char* _fileNameVS,
                         const char* _fileNameGS,
                         const char* _fileNameFS);

int invert_image(int pitch, int height, void* image_pixels);

//
int SDL_InvertSurface(SDL_Surface* image);

GLuint TextureFromFile(const char* filename);

void TextureFromFileAttach(const char* filename, GLuint role);

GLuint genSampler(GLint param_min = GL_LINEAR,
                  GLint param_mag = GL_LINEAR_MIPMAP_LINEAR);

bool errorShader(GLuint loadedShader);
bool errorLink(GLuint program);