add_library(IMGUI STATIC)

add_subdirectory("sdl2")
add_subdirectory("sdl2_image")

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

#[[
if(USE_GLES OR RASPBIAN)
    target_compile_definitions(IMGUI PUBLIC -DIMGUI_IMPL_OPENGL_ES2)

    if(RASPBIAN AND RPI_USE_BROADCOM_DRIVER)
        target_link_directories(IMGUI PUBLIC /opt/vc/lib)
        target_link_libraries(IMGUI PUBLIC brcmGLESv2 brcmEGL)
    else()
        target_link_libraries(IMGUI PUBLIC GLESv2)
    endif()
else()
    find_package(OpenGL REQUIRED)
    target_link_libraries(IMGUI PUBLIC ${OPENGL_LIBRARIES})
endif()
]]


target_link_libraries(IMGUI SDL2 SDL2_image)

