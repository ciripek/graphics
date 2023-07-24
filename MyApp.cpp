#include "MyApp.hpp"

#include <imgui.h>

#include <array>

CMyApp::CMyApp() {
    m_camera.SetView(glm::vec3(120), glm::vec3(0), glm::vec3(0, 1, 0));
}

CMyApp::~CMyApp() = default;

bool CMyApp::Init() {
    glClearColor(0.125f, 0.25f, 0.5f, 1.0f);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    m_camera.SetProj(glm::radians(60.0f), 640.0f / 480.0f, 0.01f, 1000.0f);

    setUpBuffers();

    programPipeline.useProgramStages(shaderStage::VERTEX, vertex);
    programPipeline.useProgramStages(shaderStage::FRAGMENT, fragment);
    programPipeline.validate();

    return true;
}

void CMyApp::setUpBuffers() {
    constexpr auto rectangleBuffer = std::to_array<glm::vec2>(
            {
                {-1, -1},
                {1,  -1},
                {-1, 1},
                {1,  1}
            });

    constexpr auto rectangleIndex = std::to_array<GLushort>({ 0U, 1U, 2U, 2U, 1U, 3U, });

    buffer.storage(rectangleBuffer, 0, 0);
    buffer.storage(rectangleIndex, 0, 1);

    vao.init({
        {
            .attribindex = 0,
            .size = 2,
            .type = GL_FLOAT,
            .normalized = GL_FALSE,
            .relativeoffset = 0,
            .bindingindex = 0
        },
    });

    vao.vertexArrayVertexBuffer(0, buffer[0], 0, sizeof(glm::vec2));
    vao.vertexArrayElementBuffer(buffer[1]);
}

void CMyApp::Clean() {
}

void CMyApp::Update() {
    static Uint64 last_time = SDL_GetTicks64();
    const float delta_time = (SDL_GetTicks64() - last_time) / 1000.0f;

    m_camera.Update(delta_time);

    last_time = SDL_GetTicks();
}

void CMyApp::Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    programPipeline.bind();
    vao.bind();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

    DSAVertexArrays::unbind();
    ProgramPipeline::unbind();
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
