add_library(MyOpenGL STATIC "")

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(spdlog REQUIRED)

target_sources(MyOpenGL
        PRIVATE
        BufferObjects/DSABuffers.cpp
        FrameBuffers/DSAFrameBuffers.cpp
        Mesh/DSAMesh.cpp
        Mesh/Mesh.cpp
        Utils/GLconversions.cpp
        Utils/GLDebugMessageCallback.cpp
        Utils/GLUtils.cpp
        Camera/gCamera.cpp
        Loaders/gltfLoader.cpp
        Mesh/DSAMesh.cpp
        Mesh/Mesh.cpp
        Model/Model.cpp
        Model/Material.cpp
        VertexArrays/VertexArrayObject.cpp
        Loaders/ObjParser.cpp
        Shaders/ShaderObject.cpp
        Shaders/ShaderProgram.cpp
        Shaders/ShaderProgramUniform.cpp
        Programs/ProgramObject.cpp
        Programs/ProgramPipeline.cpp
)
target_include_directories(MyOpenGL
        PUBLIC
        BufferObjects
        Camera
        FrameBuffers
        Loaders
        Mesh
        Model
        Programs
        Shaders
        Textures
        Utils
        VertexArrays
        .

        PRIVATE
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        ${OPENGL_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIRS}
        ../libs
)

target_link_libraries(MyOpenGL PRIVATE ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} spdlog::spdlog)
