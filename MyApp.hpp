#pragma once

// C++ includes
#include <memory>

// GLEW
#include <GL/glew.h>

// SDL
#include <SDL.h>
#include <SDL_opengl.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>

#include "includes/DSABuffers.hpp"
#include "includes/DSAVertexArray.hpp"
#include "includes/enums.hpp"
#include "includes/ShaderProgram.hpp"
#include "includes/gCamera.h"
#include "includes/ProgramPipelines.hpp"

class CMyApp
{
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
    DSABuffers buffer{2};
    DSAVertexArrays vao{1};

    ShaderProgram vertex = ShaderProgram::fromSPIRV("shaders/vertex.vert.spv");
    ShaderProgram fragment = ShaderProgram::fromSPIRV("shaders/fragment.frag.spv");
    ProgramPipeline programPipeline;

    void setUpBuffers();
};

