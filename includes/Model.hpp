#pragma once

#include <fmt/core.h>

#include <assimp/scene.h>
#include <filesystem>
#include <string>
#include <unordered_map>

#include "DSAMesh.hpp"
#include "DSATextures.hpp"
#include "ShaderProgram.hpp"

#include "tiny_obj_loader.h"

class Model {
public:
    explicit Model(const std::filesystem::path &name)
    {
        loadModel(name);
        for (auto& mesh:meshes) {
            mesh.initBuffers();
        }
    }

    void draw(){
        for (const auto& mesh:meshes) {
            mesh.draw(vao);
        }
    }
private :
    std::vector<DSAMesh> meshes;
    std::unordered_map<std::string, GLuint> textureMap;

    GLuint vao = DSAMesh::initVao();
    DSATexture2D textures;

    void loadModel(const std::filesystem::path &name);
    static DSAMesh loadShape(const tinyobj::attrib_t &attrib, const tinyobj::shape_t &shape, const std::vector<tinyobj::material_t> &materials);

    void loadTextures(const std::vector<tinyobj::material_t> &materials);
};
