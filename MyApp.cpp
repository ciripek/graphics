#include "MyApp.hpp"

#include <imgui.h>

#include "DSABuffers.hpp"
#include "DSATextures.hpp"

CMyApp::CMyApp() {
  m_camera.SetView(glm::vec3(120), glm::vec3(0), glm::vec3(0, 1, 0));
}

CMyApp::~CMyApp() = default;

bool CMyApp::Init() {
  if (!(vertex.isValid() && fragment.isValid())) {
    return false;
  }

  vertex.cacheUniforms();
  fragment.cacheUniforms();

  glClearColor(0.125F, 0.25F, 0.5F, 1.0F);

  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);

  m_camera.SetProj(glm::radians(60.0F), 640.0F / 480.0F, 0.01F, 1000.0F);

  return true;
    setUpBuffers();

    auto ag = std::to_array<Material>({
        {{0.0215,0.1745,0.0215},{0.07568,0.61424,0.07568},{0.633,0.727811,0.633}, glm::vec3(0.4f), 0.6},
        {{0.135, 0.2225, 0.1575}, {0.54, 0.89, 0.63},{0.316228, 0.316228,0.316228},glm::vec3(0.2f), 0.1},
        {{0.05375, 0.05, 0.06625},{0.18275, 0.17, 0.22525},{0.332741,0.328634,0.346435},glm::vec3(0.4f), 0.3},
        {{0.25, 0.20725, 0.20725},{1,0.829,0.829},{0.296648,0.296648,0.296648},glm::vec3(0.3f), 0.088},
        {{0.1745, 0.01175, 0.01175},{0.61424,0.04136,0.04136},{0.727811,0.626959,0.626959},glm::vec3(0.1f), 0.6},
    });

    buffer.storage(circlesBuffer, GL_DYNAMIC_STORAGE_BIT, 2);
    buffer.bindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, 2);

    buffer.storage(ag, 0, 3);
    buffer.bindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, 3);


    fragment.cacheUniforms();

    programPipeline.useProgramStages(shaderStage::VERTEX, vertex);
    programPipeline.useProgramStages(shaderStage::FRAGMENT, fragment);
    programPipeline.validate();

    return true;
}

void CMyApp::Clean() {}
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
  const float delta_time = (float)(SDL_GetTicks64() - last_time) / 1000.0F;

  m_camera.Update(delta_time);

  last_time = SDL_GetTicks();
}

void CMyApp::Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    programPipeline.bind();
    vao.bind();

    fragment.setUniform("cam.eye", m_camera.GetEye());
    fragment.setUniform("cam.at", m_camera.GetAt());
    fragment.setUniform("cam.up", m_camera.GetUp());

    fragment.setUniform("window", window_size);

    fragment.setUniform("fovy", fovy);
    fragment.setUniform("fovx", fovx);
    fragment.setUniform("reflection", reflect);

    buffer.subData(circlesBuffer, 0, 2);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

    DSAVertexArrays::unbind();
    ProgramPipeline::unbind();

    renderImgui();
}

void CMyApp::renderImgui() {
    ImGui::Begin("Demo window");

    ImGui::SliderInt("Reflect", &reflect, 1, 100);
    for (int i = 0; i < circlesBuffer.size(); ++i) {
        ImGui::Text("Circle %d", i);
        ImGui::SliderFloat3(fmt::format("##{}", i).c_str(), glm::value_ptr(circlesBuffer[i].center),-50.f, 50.f);
        ImGui::SliderFloat(fmt::format("##{}", i).c_str(), &(circlesBuffer[i].radius), 1.f, 20.f);
    }

    ImGui::Text("exe : %f, %f, %f", m_camera.GetEye().x, m_camera.GetEye().y, m_camera.GetEye().z);
    ImGui::Text("at : %f, %f, %f", m_camera.GetAt().x, m_camera.GetAt().y, m_camera.GetAt().z);
    ImGui::Text("up : %f, %f, %f", m_camera.GetUp().x, m_camera.GetUp().y, m_camera.GetUp().z);


    ImGui::End();

}

void CMyApp::KeyboardDown(SDL_KeyboardEvent& key) {
  m_camera.KeyboardDown(key);
}

void CMyApp::KeyboardUp(SDL_KeyboardEvent& key) {
  m_camera.KeyboardUp(key);
}

void CMyApp::MouseMove(SDL_MouseMotionEvent& mouse) {
  m_camera.MouseMove(mouse);
}

void CMyApp::MouseDown(SDL_MouseButtonEvent& mouse) {}

void CMyApp::MouseUp(SDL_MouseButtonEvent& mouse) {}

void CMyApp::MouseWheel(SDL_MouseWheelEvent& wheel) {}

void CMyApp::Resize(int width, int height) {
    glViewport(0, 0, width, height);
    window_size = {width, height};
    m_camera.Resize(width, height);

    aspect = window_size.x / window_size.y;
    fovx = 2 * std::atan(std::tan(fovy / 2) * aspect);
}
