
#include <GL/glew.h>


#include <SDL.h>


#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl2.h>


#include <fmt/core.h>

#include "includes/GLDebugMessageCallback.h"

#include "MyApp.hpp"

int main(int argc, char *args[]) {
    if (SDL_Init(SDL_INIT_VIDEO) == -1) {
        fmt::println("[SDL init] Error while initializing SDL: {}", SDL_GetError());
        return 1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#ifndef NDEBUG

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
#endif

    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    //SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,  1);
    //SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,  2);

    SDL_Window *win = SDL_CreateWindow("Hello SDL&OpenGL!",
                                       100, 100,
                                       640, 480,
                                       SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (win == nullptr) {
        fmt::println("[Window creation] Error while initializing SDL: {}", SDL_GetError());
        return 1;
    }

    SDL_GLContext context = SDL_GL_CreateContext(win);
    if (context == nullptr) {
        fmt::println("[OGL context creation] Error while initializing SDL: {}", SDL_GetError());
        return 1;
    }

    SDL_GL_SetSwapInterval(1);

    GLenum error = glewInit();
    if (error != GLEW_OK) {
        fmt::println("[GLEW] Error while init: {}", (char*)glewGetErrorString(error));
        return 1;
    }

    int glVersion[2] = {-1, -1};
    glGetIntegerv(GL_MAJOR_VERSION, &glVersion[0]);
    glGetIntegerv(GL_MINOR_VERSION, &glVersion[1]);
    fmt::println("Running OpenGL {}.{}", glVersion[0], glVersion[1]);

    if (glVersion[0] == -1 && glVersion[1] == -1) {
        SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(win);

        fmt::println("[OGL context creation] Could not create OGL context! "
                     "SDL_GL_SetAttribute(...) calls may have wrong settings.");

        return 1;
    }

    SDL_SetWindowTitle(win, fmt::format("OpenGL {}.{}", glVersion[0], glVersion[1]).c_str());

    GLint context_flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &context_flags);
    if (context_flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);
        glDebugMessageCallback(GLDebugMessageCallback, nullptr);
    }


    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForOpenGL(win, context);
    ImGui_ImplOpenGL3_Init("#version 460");


    {
        bool quit = false;

        SDL_Event ev;

        CMyApp app;
        if (!app.Init()) {
            SDL_GL_DeleteContext(context);
            SDL_DestroyWindow(win);
            fmt::println("[app.Init] Error while app init!");
            return 1;
        }
        int w, h;
        SDL_GetWindowSize(win, &w, &h);
        app.Resize(w, h);

        while (!quit) {
            while (SDL_PollEvent(&ev)) {
                ImGui_ImplSDL2_ProcessEvent(&ev);
                bool is_mouse_captured = ImGui::GetIO().WantCaptureMouse;
                bool is_keyboard_captured = ImGui::GetIO().WantCaptureKeyboard;
                switch (ev.type) {
                    case SDL_QUIT:
                        quit = true;
                        break;
                    case SDL_KEYDOWN:
                        if (ev.key.keysym.sym == SDLK_ESCAPE)
                            quit = true;
                        if (!is_keyboard_captured)
                            app.KeyboardDown(ev.key);
                        break;
                    case SDL_KEYUP:
                        if (!is_keyboard_captured)
                            app.KeyboardUp(ev.key);
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        if (!is_mouse_captured)
                            app.MouseDown(ev.button);
                        break;
                    case SDL_MOUSEBUTTONUP:
                        if (!is_mouse_captured)
                            app.MouseUp(ev.button);
                        break;
                    case SDL_MOUSEWHEEL:
                        if (!is_mouse_captured)
                            app.MouseWheel(ev.wheel);
                        break;
                    case SDL_MOUSEMOTION:
                        if (!is_mouse_captured)
                            app.MouseMove(ev.motion);
                        break;
                    case SDL_WINDOWEVENT:
                        if (ev.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                            app.Resize(ev.window.data1, ev.window.data2);
                        }
                        break;
                }

            }
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplSDL2_NewFrame();
            ImGui::NewFrame();

            app.Update();
            app.Render();

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            SDL_GL_SwapWindow(win);
        }

        app.Clean();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}