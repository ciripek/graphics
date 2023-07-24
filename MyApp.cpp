#include "MyApp.hpp"

#include <imgui.h>

CMyApp::CMyApp() {
    m_camera.SetView(glm::vec3(120), glm::vec3(0), glm::vec3(0, 1, 0));
}

CMyApp::~CMyApp() = default;

bool CMyApp::Init() {
    glClearColor(0.125f, 0.25f, 0.5f, 1.0f);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    m_camera.SetProj(glm::radians(60.0f), 640.0f / 480.0f, 0.01f, 1000.0f);

    return true;
}

void CMyApp::Clean() {
}

void CMyApp::Update() {
    static Uint64 last_time = SDL_GetTicks64();
    float delta_time = (SDL_GetTicks64() - last_time) / 1000.0f;

    m_camera.Update(delta_time);

    last_time = SDL_GetTicks();
}

void CMyApp::Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
