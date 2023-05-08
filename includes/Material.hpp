#pragma once


#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

#include <assimp/material.h>

struct TextureInfo{
    aiTextureType type;
    GLuint id{};
};


struct Material {
    std::vector<TextureInfo> textures;
    glm::vec3 Ka, Ks, Ke;
    GLfloat Ns, Ni, d;
};
