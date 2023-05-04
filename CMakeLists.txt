cmake_minimum_required(VERSION 3.25)
project(Base)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_subdirectory("libs")

file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/includes/*.cpp
        ${PROJECT_SOURCE_DIR}/includes/*.hpp
        ${PROJECT_SOURCE_DIR}/includes/*.inl)

set(EXTERNAL IMGUI fmt)

add_executable(${PROJECT_NAME} main.cpp MyApp.cpp MyApp.hpp ${SRC_FILES})
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS} ${ASSIMP_INCLUDE_DIRS} ${EXTERNAL})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${ASSIMP_LIBRARIES} ${EXTERNAL})
