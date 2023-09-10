#include "gltfLoader.hpp"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define TINYGLTF_NOEXCEPTION  // optional. disable exception handling.
#define TINYGLTF_USE_CPP14

#include "tiny_gltf.h"

#include "spdlog-config.hpp"

gltfLoader::gltfLoader(const std::filesystem::path &path) {
    tinygltf::TinyGLTF loader;
    tinygltf::Model model;
    std::string err;
    std::string warn;

    const bool res = loader.LoadBinaryFromFile(&model, &err, &warn, path.string());

    if (!warn.empty()) {
        fmt::println("WARN: {}", warn);
    }

    if (!err.empty()) {
        fmt::println(stderr, "ERR: {}", err);
    }

    if (!res) {
        SPDLOG_ERROR(LOG_STRING("Failed to load glTF: {}"), path.native());
    } else {
        SPDLOG_INFO(LOG_STRING("Loaded glTF: {}"), path.native());
    }
}

gltfLoader::~gltfLoader() = default;