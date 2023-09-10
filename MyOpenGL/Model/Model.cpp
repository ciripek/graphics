#include "Model.hpp"

#include "ShaderProgram.hpp"

#include <filesystem>
#include <unordered_map>

#define TINYOBJLOADER_DONOT_INCLUDE_MAPBOX_EARCUT
#define TINYOBJLOADER_IMPLEMENTATION
#define TINYOBJLOADER_USE_MAPBOX_EARCUT
#include "earcut.hpp"
#include "tiny_obj_loader.h"

#include "spdlog-config.hpp"

void Model::loadModel(const std::filesystem::path& name) {
  tinyobj::ObjReader reader;

  if (!reader.ParseFromFile(name.string())) {
    if (!reader.Error().empty()) {
      SPDLOG_ERROR("TinyObjReader: {}", reader.Error());
    }
    return;
  }

  const auto& attrib = reader.GetAttrib();
  const auto& shapes = reader.GetShapes();
  material = reader.GetMaterials();

  loadTextures(material, name.parent_path());
  buffers = DSABuffers(shapes.size() * 2);
  count.resize(shapes.size() * 2);

  for (int i = 0; const auto& shape : shapes) {
    loadShape(attrib, shape, i);
    i += 2;
  }
}

// https://blog.42yeah.is/rendering/2023/04/08/tinyobjloader.html
void Model::loadShape(const tinyobj::attrib_t& attrib,
                      const tinyobj::shape_t& shape,
                      int index) {
  std::vector<vertex> verts;
  std::vector<GLuint> indices;

  std::unordered_map<Model::vertex, GLuint> uniqueVertices;
  for (const auto& i : shape.mesh.indices) {
    const vertex vert{.position{attrib.vertices[i.vertex_index * 3],
                                attrib.vertices[i.vertex_index * 3 + 1],
                                attrib.vertices[i.vertex_index * 3 + 2]},
                      .normal{attrib.normals[i.normal_index * 3],
                              attrib.normals[i.normal_index * 3 + 1],
                              attrib.normals[i.normal_index * 3 + 2]},
                      .texcoord{
                          attrib.texcoords[i.texcoord_index * 2],
                          attrib.texcoords[i.texcoord_index * 2 + 1],
                      }};

    if (!uniqueVertices.contains(vert)) {
      uniqueVertices[vert] = static_cast<GLuint>(verts.size());
      verts.push_back(vert);
    }
    indices.push_back(uniqueVertices[vert]);
  }

  buffers.storage(verts, 0, index);
  buffers.storage(indices, 0, index + 1);
  count[index] = shape.mesh.material_ids[0];
  count[index + 1] = indices.size();
}

void Model::loadTextures(const std::vector<tinyobj::material_t>& materials,
                         const std::filesystem::path& name) {
  for (const auto& mat : materials) {
    insertMatText(mat.ambient_texname);
    insertMatText(mat.diffuse_texname);
    insertMatText(mat.specular_texname);
    insertMatText(mat.specular_highlight_texname);
    insertMatText(mat.bump_texname);
    insertMatText(mat.displacement_texname);
    insertMatText(mat.alpha_texname);
    insertMatText(mat.reflection_texname);
  }

  textures = DSATexture2D(textureMap.size());
  for (int i = 0; const auto& [key, value] : textureMap) {
    textures.AttachFromFile(name / key, true, i);
    textureMap[key] = textures[i];
    ++i;
  }
}

void Model::insertMatText(const std::string& MatText) {
  if (!MatText.empty()) {
    textureMap.insert({MatText, 0});
  }
}

void Model::draw(ShaderProgram& program) {
  for (int i = 0; i < buffers.getBufferCount(); i += 2) {
    glBindVertexArray(vao);

    glVertexArrayVertexBuffer(vao, 0, buffers[i], 0, sizeof(vertex));
    glVertexArrayElementBuffer(vao, buffers[i + 1]);

    setUniforms(program, i);

    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(count[i + 1]),
                   GL_UNSIGNED_INT, nullptr);

    glBindVertexArray(0);
  }
}

void Model::setUniforms(ShaderProgram& program, int i) {
  const tinyobj::material_t& mat = material[count[i]];

  program.setUniform("Ns", mat.shininess);
  program.setUniform("Ka", mat.ambient[0], mat.ambient[1], mat.ambient[2]);
  program.setUniform("Ks", mat.specular[0], mat.specular[1], mat.specular[2]);
  program.setUniform("Ke", mat.emission[0], mat.emission[1], mat.emission[2]);
  program.setUniform("Ni", mat.ior);
  program.setUniform("d", mat.dissolve);
  program.setUniform("illum", mat.illum);

  program.setTexture("map_Kd", 0, textureMap[mat.diffuse_texname]);
}
