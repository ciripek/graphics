#pragma once

// C++ includes
#include <memory>
#include <array>
#include <numbers>
#include <cmath>

// GLEW
#include <GL/glew.h>

// SDL
#include <SDL.h>
#include <SDL_opengl.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>

#include "DSABufferStatic.hpp"
#include "DSABufferStaticArray.hpp"
#include "Model.hpp"
#include "ProgramPipeline.hpp"
#include "ShaderProgram.hpp"
#include "enums.hpp"
#include "gCamera.h"

class CMyApp {
 public:
  CMyApp();
  ~CMyApp();

  DELETE_COPY(CMyApp)
  DEFAULT_MOVE(CMyApp)

  bool Init();
  void Clean();

  void Update();
  void Render();

  void KeyboardDown(SDL_KeyboardEvent&);
  void KeyboardUp(SDL_KeyboardEvent&);
  void MouseMove(SDL_MouseMotionEvent&);
  void MouseDown(SDL_MouseButtonEvent&);
  void MouseUp(SDL_MouseButtonEvent&);
  void MouseWheel(SDL_MouseWheelEvent&);
  void Resize(int, int);

private:
	gCamera				m_camera;
    DSABuffers buffer{4};
    DSAVertexArrays vao{1};

    ShaderProgram vertex = ShaderProgram::fromSPIRV("shaders/vertex.vert.spv");
    ShaderProgram fragment = ShaderProgram::fromSPIRV("shaders/fragment.frag.spv");
    ProgramPipeline programPipeline;

    void setUpBuffers();

    struct circle {
        glm::vec3 center;
        glm::float32 radius;
    };

    struct Material {
        glm::vec3 ambient;
        alignas(sizeof(glm::vec4)) glm::vec3 diffuse;
        alignas(sizeof(glm::vec4)) glm::vec3 specular;
        alignas(sizeof(glm::vec4)) glm::vec3 reflect_color;
        glm::float32 shininess;
    };

    glm::vec2 window_size = {640.f, 480.f };
    glm::float32 aspect = window_size.x / window_size.y;

    static constexpr glm::float32 fovy = glm::radians(25.F);
    glm::float32 fovx = 2 * std::atan(std::tan(fovy / 2) * aspect);
    glm::int32 reflect = 1;


    std::array<circle, 5> circlesBuffer = std::to_array<circle>({{{5,5,10},10}, {{15,15,15},3}, {{-13,13,13},3},
                                                                 {{13,-13,13},6}, {{-13,13,-13},8}});


    void renderImgui();
};
