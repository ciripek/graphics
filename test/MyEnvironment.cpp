#include "MyEnvironment.hpp"

#include <GL/glew.h>
#include <SDL.h>

#include "GLDebugMessageCallback.h"

void MyEnvironment::SetUp() {
  SDL_Init(SDL_INIT_VIDEO);
  window = SDL_CreateWindow("Hello SDL&OpenGL!", 100, 100, 640, 480,
                            SDL_WINDOW_OPENGL);
  context = SDL_GL_CreateContext(window);

  glewInit();

  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
  glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE,
                        GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);
  glDebugMessageCallback(GLDebugMessageCallback, nullptr);
}

void MyEnvironment::TearDown() {
  SDL_GL_DeleteContext(context);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
