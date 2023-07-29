#include "gltfLoader.hpp"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define TINYGLTF_NOEXCEPTION // optional. disable exception handling.
#define TINYGLTF_USE_CPP14
#include "tiny_gltf.h"

#include <fmt/core.h>

gltfLoader::gltfLoader(const std::filesystem::path& path) {
    tinygltf::TinyGLTF loader;
    tinygltf::Model model;
    std::string err;
    std::string warn;

    const bool res = loader.LoadBinaryFromFile(&model, &err, &warn, path);

    if (!warn.empty()) {
        fmt::println("WARN: {}", warn);
    }

    if (!err.empty()) {
        fmt::println(stderr, "ERR: {}", err);
    }

    if (!res) {
        fmt::println(stderr, "Failed to load glTF: {}", path.native());
    }
    else{
        fmt::println("Loaded glTF: {}", path.native());
    }
}

gltfLoader::~gltfLoader() = default;