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

#include "includes/gCamera.h"

#include "includes/BufferObject.h"
#include "includes/ProgramObject.h"
#include "includes/TextureObject.h"
#include "includes/VertexArrayObject.h"

// mesh
#include "includes/Model.hpp"
#include "includes/ObjParser.hpp"
#include "includes/ProgramPipelines.hpp"
#include "includes/ShaderProgram.hpp"
#include "includes/DSATextures.hpp"

class CMyApp
{
public:
	CMyApp();
	~CMyApp();

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

    Model model {"assets/kocka.obj"};

    ShaderProgram vertex = ShaderProgram::fromGLSL("myVert.vert");
    ShaderProgram fragment = ShaderProgram::fromGLSL("myFrag.frag");
    ProgramPipeline programPipelines;
    DSATexture2D texture{1};

    struct Vertex
	{
		glm::vec3 p;
		glm::vec3 n;
		glm::vec2 t;
	};
};

