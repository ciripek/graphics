#pragma once

#include <fmt/core.h>

#include <assimp/scene.h>
#include <filesystem>
#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>
#include <string>
#include <unordered_map>

#include "DSABuffers.hpp"
#include "DSAMesh.hpp"
#include "DSATextures.hpp"
#include "ShaderProgram.hpp"

#include "tiny_obj_loader.h"

class Model {
 public:
  explicit Model(const std::filesystem::path& name) { loadModel(name); }

  void draw(ShaderProgram& program);

  struct vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texcoord;

    bool operator==(const vertex& other) const = default;
  };

 private:
  std::vector<tinyobj::material_t> material;
  std::unordered_map<std::string, GLuint> textureMap;

  GLuint vao = DSAMesh::initVao();
  DSATexture2D textures;
  std::vector<GLuint> count;
  DSABuffers buffers;

  void loadModel(const std::filesystem::path& name);
  void loadShape(const tinyobj::attrib_t& attrib,
                 const tinyobj::shape_t& shape,
                 int index);

  void loadTextures(const std::vector<tinyobj::material_t>& materials,
                    const std::filesystem::path& name);
  void insertMatText(const std::string& MatText);

  void setUniforms(ShaderProgram& program, int i);
};

template <>
struct std::hash<Model::vertex> {
  std::size_t operator()(const Model::vertex& v) const noexcept {
    using std::hash;
    using std::size_t;
    using std::string;

    return ((hash<glm::vec3>()(v.position) ^
             (hash<glm::vec3>()(v.normal) << 1)) >>
            1) ^
           (hash<glm::vec2>()(v.texcoord) << 1);
  }
};
