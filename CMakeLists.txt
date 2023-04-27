cmake_minimum_required(VERSION 3.25)
project(Base)

set(CMAKE_CXX_STANDARD 23)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

add_subdirectory("libs")

file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/includes/*.cpp
        ${PROJECT_SOURCE_DIR}/includes/*.hpp
        ${PROJECT_SOURCE_DIR}/includes/*.inl)

add_executable(${PROJECT_NAME} main.cpp MyApp.cpp MyApp.h ${SRC_FILES})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS} IMGUI SDL2 SDL2_image)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} IMGUI SDL2 SDL2_image)
