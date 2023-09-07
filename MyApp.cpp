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
}

void CMyApp::Clean() {}

void CMyApp::Update() {
  static Uint64 last_time = SDL_GetTicks64();
  const float delta_time = (float)(SDL_GetTicks64() - last_time) / 1000.0F;

  m_camera.Update(delta_time);

  last_time = SDL_GetTicks();
}

void CMyApp::Render() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  const glm::mat4 viewProj = m_camera.GetViewProj();

  const glm::mat4 suzanneWorld = glm::mat4(1.0F);

  programPipelines.bind();

  programPipelines.useProgramStages(shaderStage::VERTEX, vertex);
  programPipelines.useProgramStages(shaderStage::FRAGMENT, fragment);

  vertex.setUniform("MVP", viewProj * suzanneWorld);
  vertex.setUniform("world", suzanneWorld);
  vertex.setUniform("worldIT", glm::inverse(glm::transpose(suzanneWorld)));

  fragment.setUniform("viewPos", m_camera.GetEye());

  model.draw(fragment);
  ProgramPipeline::unbind();

  ImGui::ShowDemoWindow();
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

  m_camera.Resize(width, height);
}
