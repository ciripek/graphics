#include "ShaderObject.h"

#include <fstream>
#include <iostream>

#include "GLUtils.hpp"

ShaderObject::ShaderObject(GLenum pType) : m_id(glCreateShader(pType)) {

}

ShaderObject::~ShaderObject() {
    if (m_id != 0) {
        glDeleteShader(m_id);
        m_id = 0;
    }
}

ShaderObject::ShaderObject(ShaderObject &&rhs) {
    m_id = rhs.m_id;
    rhs.m_id = 0;
}

ShaderObject &ShaderObject::operator=(ShaderObject &&rhs) {
    if (&rhs == this)
        return *this;

    m_id = rhs.m_id;
    rhs.m_id = 0;

    return *this;
}

ShaderObject::ShaderObject(GLenum pType, const std::string &pFilenameOrSource) : m_id(glCreateShader(pType)) {
    if (!FromFile(pFilenameOrSource.c_str())) {
        if (!std::ifstream(pFilenameOrSource).good()) {
            FromMemory(pFilenameOrSource);
        }
    }
}

bool ShaderObject::FromFile(const std::filesystem::path &fileName) const {
    auto file = loadFile(fileName);
    if (!file) {
        return false;
    }

    return CompileShaderFromMemory(m_id, *file) > 0;
}

bool ShaderObject::FromMemory(const std::string &_source) const {
    CompileShaderFromMemory(m_id, _source);
    return m_id != 0;
}

GLuint ShaderObject::CompileShaderFromMemory(GLuint _shaderObject, const std::string &_source) {
    // betoltott kod hozzarendelese a shader-hez
    const char *sourcePointer = _source.c_str();
    glShaderSource(_shaderObject, 1, &sourcePointer, nullptr);

    // shader leforditasa
    glCompileShader(_shaderObject);

    if (!errorShader(_shaderObject)){
        return 0;
    }
    return _shaderObject;
}