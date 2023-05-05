#include "MyApp.hpp"

#include <imgui.h>

#include "includes/GLUtils.hpp"

CMyApp::CMyApp() {
    m_camera.SetView(glm::vec3(5, 5, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
}

CMyApp::~CMyApp() = default;

bool CMyApp::Init() {
    ShaderProgram vertex = ShaderProgram::fromSPIRV("test.vert.spv");
    //ShaderProgram vertex = ShaderProgram::fromSPIRV("vert.spv", shaderType::VERTEX);
    vertex.cacheUniforms();

    glClearColor(0.125f, 0.25f, 0.5f, 1.0f);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);


    m_program.AttachShaders({
                                    {GL_VERTEX_SHADER,   "myVert.vert"},
                                    {GL_FRAGMENT_SHADER, "myFrag.frag"}
                            });

    m_program.LinkProgram();

    m_suzanneTexture.FromFile("assets/marron.jpg");

    model.init();

    m_camera.SetProj(glm::radians(60.0f), 640.0f / 480.0f, 0.01f, 1000.0f);

    return true;
}

void CMyApp::Clean() {
}

void CMyApp::Update() {
    static Uint32 last_time = SDL_GetTicks();
    float delta_time = (SDL_GetTicks() - last_time) / 1000.0f;

    m_camera.Update(delta_time);

    last_time = SDL_GetTicks();
}

void CMyApp::Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 viewProj = m_camera.GetViewProj();

    glm::mat4 suzanneWorld = glm::mat4(1.0f);

    m_program.Use();
    m_program.SetTexture("texImage", 0, m_suzanneTexture);
    m_program.SetUniform("MVP", viewProj * suzanneWorld);
    m_program.SetUniform("world", suzanneWorld);
    m_program.SetUniform("worldIT", glm::inverse(glm::transpose(suzanneWorld)));
    model.draw();

    m_program.Unuse();

    ImGui::ShowDemoWindow();
}

void CMyApp::KeyboardDown(SDL_KeyboardEvent &key) {
    m_camera.KeyboardDown(key);
}

void CMyApp::KeyboardUp(SDL_KeyboardEvent &key) {
    m_camera.KeyboardUp(key);
}

void CMyApp::MouseMove(SDL_MouseMotionEvent &mouse) {
    m_camera.MouseMove(mouse);
}

void CMyApp::MouseDown(SDL_MouseButtonEvent &mouse) {
}

void CMyApp::MouseUp(SDL_MouseButtonEvent &mouse) {
}

void CMyApp::MouseWheel(SDL_MouseWheelEvent &wheel) {
}

void CMyApp::Resize(int _w, int _h) {
    glViewport(0, 0, _w, _h);

    m_camera.Resize(_w, _h);
}
