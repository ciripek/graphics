add_library(IMGUI STATIC)

add_subdirectory("sdl2")
add_subdirectory("sdl2_image")
add_subdirectory("fmt")

target_sources(IMGUI
        PRIVATE
        imgui/imgui_demo.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp
        imgui/imgui.cpp

        PRIVATE
        imgui/backends/imgui_impl_opengl3.cpp
        imgui/backends/imgui_impl_sdl2.cpp
        )

target_include_directories(IMGUI
        PUBLIC imgui
        PUBLIC imgui/backends
        PRIVATE SDL2
        PRIVATE SDL2_image
        )

target_link_libraries(IMGUI SDL2 SDL2_image)

