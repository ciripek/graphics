#pragma once

#include <assimp/scene.h>
#include <string>

#include "DSAMesh.hpp"

class Model {
public:
    explicit Model(const std::string &name)
    {
        loadModel(name);
    }
    void draw();
    void init();
private:
    // model data
    std::vector<DSAMesh> meshes;

    void loadModel(const std::string &name);
    void processNode(aiNode *node, const aiScene *scene);
    DSAMesh processMesh(aiMesh *mesh, const aiScene *scene);
};
