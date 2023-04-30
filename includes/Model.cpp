#include "Model.hpp"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <fmt/core.h>

void Model::draw() {
    for (const DSAMesh &dsaMesh: meshes  ) {
        dsaMesh.draw();
    }
}

void Model::loadModel(const std::string &name) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(name, aiProcess_Triangulate | aiProcess_FlipUVs);

    if((scene == nullptr) || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || (scene->mRootNode == nullptr))
    {
        fmt::println(stderr, "Assimp error: {}", importer.GetErrorString());
        return;
    }

    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene) {
    // process all the node's meshes (if any)
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    // then do the same for each of its children
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

DSAMesh Model::processMesh(aiMesh *mesh, const aiScene *scene) {
    DSAMesh dsaMesh;

    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        DSAMesh::vertex vertex{};

        vertex.position = {mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z};

        if (mesh->HasNormals())
        {
            vertex.normal = {mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z};
        }
        // texture coordinates
        if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            vertex.texcoord = {mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y};
        }
        else{
            vertex.texcoord = glm::vec2(0.0f, 0.0f);
        }

        dsaMesh.addVertex(vertex);
    }
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        const aiFace face = mesh->mFaces[i];

        for(unsigned int j = 0; j < face.mNumIndices; j++){
            dsaMesh.addIndex(face.mIndices[j]);
        }
    }

    return dsaMesh;
}

void Model::init() {
    for (DSAMesh &dsaMesh: meshes  ) {
        dsaMesh.initBuffers();
    }
}
