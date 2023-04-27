#include "MyApp.hpp"


#include <array>

CMyApp::CMyApp(void)
{
	m_camera.SetView(glm::vec3(5, 5, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
}

CMyApp::~CMyApp(void)
{
}

void CMyApp::InitCube()
{
	Vertex vert[] =
	{
		{glm::vec3(-1, -1, 0)},
		{glm::vec3(1, -1, 0)},
		{glm::vec3(-1,  1, 0)},
		{glm::vec3(1,  1, 0)},
	};
	GLushort indices[] =
	{
		0U,1U,2U,
		2U,1U,3U,
	};

	m_CubeVertexBuffer.BufferData(vert);
	m_CubeIndices.BufferData(indices);
	m_CubeVao.Init({{ CreateAttribute<0,glm::vec3,0,sizeof(Vertex)>, m_CubeVertexBuffer }},m_CubeIndices);
}


void CMyApp::InitShaders()
{
	m_program.AttachShaders({{ GL_VERTEX_SHADER, "myVert.vert"},{ GL_FRAGMENT_SHADER, "myFrag.frag"}});
	m_program.LinkProgram();
}

bool CMyApp::Init()
{
	glClearColor(0.125f, 0.25f, 0.5f, 1.0f);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	InitShaders();
	InitCube();

	m_camera.SetProj(glm::radians(60.0f), 640.0f / 480.0f, 0.01f, 1000.0f);

	return true;
}

void CMyApp::Clean()
{
}

void CMyApp::Update()
{
	static Uint32 last_time = SDL_GetTicks();
	float delta_time = (SDL_GetTicks() - last_time) / 1000.0f;

	m_camera.Update(delta_time);

	last_time = SDL_GetTicks();
}

void CMyApp::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_program.Use();

	glm::vec4 gombok[] = { {0,0,0,10}, {15,15,15,10}, {-13,13,13,3},  {13,-13,13,6},  {-13,13,-13,8}, {-13,-13,-13, 2}, {0,20,13,2} };
	for (int i = 0; i < std::size(gombok); ++i) {
		std::string name = "gombok[" + std::to_string(i) + "]";
		m_program.SetUniform(name.c_str(), gombok[i]);
	}

	feny fenyek[] = { {{-13,-13,-13}, glm::vec3(0.1)}, {{0,20,13}, glm::vec3(0.3)}};
	for ( int i = 0; i < std::size(fenyek); i++)
	{
		std::string one = "fenyek[" + std::to_string(i) + "].pos";
		std::string two = "fenyek[" + std::to_string(i) + "].color";

		m_program.SetUniform(one.c_str(), fenyek[i].p);
		m_program.SetUniform(two.c_str(), fenyek[i].c);
	}
	anyag ag[5] = { 
		{{0.0215,0.1745,0.0215},{0.07568,0.61424,0.07568},{0.633,0.727811,0.633}, 0.6}, 
		{{0.135, 0.2225, 0.1575}, {0.54, 0.89, 0.63},{0.316228, 0.316228,0.316228},0.1},
		{{0.05375, 0.05, 0.06625},{0.18275, 0.17, 0.22525},{0.332741,0.328634,0.346435},0.3},
		{{0.25, 0.20725, 0.20725},{1,0.829,0.829},{0.296648,0.296648,0.296648},0.088},
		{{0.1745, 0.01175, 0.01175},{0.61424,0.04136,0.04136},{0.727811,0.626959,0.626959},0.6},
	};
	for (int i = 0; i < std::size(ag); i++) {
		std::string one = "anyagok[" + std::to_string(i) + "].ambient";
		std::string two = "anyagok[" + std::to_string(i) + "].diffuse";
		std::string three = "anyagok[" + std::to_string(i) + "].specular";
		std::string four = "anyagok[" + std::to_string(i) + "].shininess";

		m_program.SetUniform(one.c_str(), ag[i].ambient);
		m_program.SetUniform(two.c_str(), ag[i].diffuse);
		m_program.SetUniform(three.c_str(), ag[i].specular);
		m_program.SetUniform(four.c_str(), ag[i].shininess);
	}


	m_program.SetUniform("cam.eye", m_camera.GetEye());
	m_program.SetUniform("cam.at", m_camera.GetAt());
	m_program.SetUniform("cam.up", m_camera.GetUp());
	m_CubeVao.Bind();


	glDrawElements(GL_TRIANGLES,
		6,
		GL_UNSIGNED_SHORT,
		nullptr);
	


	m_program.Unuse();

}

void CMyApp::KeyboardDown(SDL_KeyboardEvent& key)
{
	m_camera.KeyboardDown(key);
}

void CMyApp::KeyboardUp(SDL_KeyboardEvent& key)
{
	m_camera.KeyboardUp(key);
}

void CMyApp::MouseMove(SDL_MouseMotionEvent& mouse)
{
	m_camera.MouseMove(mouse);
}

void CMyApp::MouseDown(SDL_MouseButtonEvent& mouse)
{
}

void CMyApp::MouseUp(SDL_MouseButtonEvent& mouse)
{
}

void CMyApp::MouseWheel(SDL_MouseWheelEvent& wheel)
{
}

void CMyApp::Resize(int _w, int _h)
{
	glViewport(0, 0, _w, _h );
	aspect = _w / (float)_h;
	res = { _w, _h };
	m_camera.Resize(_w, _h);
}
