#include "Model.hpp"

#include "ShaderProgram.hpp"

#include <filesystem>
#include <unordered_map>
#include <fmt/core.h>

#define TINYOBJLOADER_DONOT_INCLUDE_MAPBOX_EARCUT
#define TINYOBJLOADER_IMPLEMENTATION
#define TINYOBJLOADER_USE_MAPBOX_EARCUT
#include "earcut.hpp"
#include "tiny_obj_loader.h"

void Model::loadModel(const std::filesystem::path &name) {
    tinyobj::ObjReader reader;

    if (!reader.ParseFromFile(name)) {
        if (!reader.Error().empty()) {
            fmt::println(stderr, "TinyObjReader: {}", reader.Error());
        }
        return;
    }

    const auto& attrib = reader.GetAttrib();
    const auto& shapes = reader.GetShapes();
    const auto& materials = reader.GetMaterials();

    loadTextures(materials);

    for (const auto& shape: shapes) {
        meshes.push_back(loadShape(attrib, shape, materials));
    }
}

// https://blog.42yeah.is/rendering/2023/04/08/tinyobjloader.html
DSAMesh Model::loadShape(const tinyobj::attrib_t &attrib, const tinyobj::shape_t &shape,
                      const std::vector<tinyobj::material_t> &materials) {
    DSAMesh dsaMesh{};
    std::unordered_map<DSAMesh::vertex, GLuint> uniqueVertices;
    dsaMesh.setMaterial(materials[shape.mesh.material_ids[0]]);
    for (const auto &i : shape.mesh.indices) {

        const DSAMesh::vertex  vert {
            .position {
                attrib.vertices[i.vertex_index * 3],
                attrib.vertices[i.vertex_index * 3 + 1],
                attrib.vertices[i.vertex_index * 3 + 2]
            },
            .normal {
                attrib.normals[i.normal_index * 3],
                attrib.normals[i.normal_index * 3 + 1],
                attrib.normals[i.normal_index * 3 + 2]
            },
            .texcoord {
                attrib.texcoords[i.texcoord_index * 2],
                attrib.texcoords[i.texcoord_index * 2 + 1],
            }
        };

        if (!uniqueVertices.contains(vert)){
            uniqueVertices[vert] = static_cast<GLuint>(dsaMesh.vertexSize());
            dsaMesh.addVertex(vert);
        }
        dsaMesh.addIndex(uniqueVertices[vert]);
    }

    return dsaMesh;
}

void Model::loadTextures(const std::vector<tinyobj::material_t> &materials) {
    for (const auto& mat: materials) {
        if (!mat.ambient_texname.empty()){
            textureMap.insert({mat.ambient_texname, 0});
        }
        if (!mat.diffuse_texname.empty()){
            textureMap.insert({mat.diffuse_texname, 0});
        }
        if (!mat.ambient_texname.empty()){
            textureMap.insert({mat.ambient_texname, 0});
        }
        if (!mat.ambient_texname.empty()){
            textureMap.insert({mat.ambient_texname, 0});
        }
        if (!mat.ambient_texname.empty()){
            textureMap.insert({mat.ambient_texname, 0});
        }
        if (!mat.ambient_texname.empty()){
            textureMap.insert({mat.ambient_texname, 0});
        }
        if (!mat.ambient_texname.empty()){
            textureMap.insert({mat.ambient_texname, 0});
        }
        if (!mat.ambient_texname.empty()){
            textureMap.insert({mat.ambient_texname, 0});
        }
    }
}
