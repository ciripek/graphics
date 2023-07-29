add_library(IMGUI STATIC)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
add_subdirectory("fmt")

target_sources(IMGUI
        PUBLIC
        imgui/imgui_demo.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp
        imgui/imgui.cpp

        PUBLIC
        imgui/backends/imgui_impl_opengl3.cpp
        imgui/backends/imgui_impl_sdl2.cpp
        )

target_include_directories(IMGUI
        PUBLIC imgui
        PUBLIC imgui/backends
        PRIVATE ${SDL2_INCLUDE_DIRS}
        PRIVATE ${SDL2_IMAGE_INCLUDE_DIRS}
        )

target_link_libraries(IMGUI ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

