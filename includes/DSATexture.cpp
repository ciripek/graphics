#include "DSATexture.hpp"

DSATexture::DSATexture(DSATextureType type) {
    glCreateTextures(static_cast<GLenum>(type), 1, &m_id);
}

DSATexture::DSATexture(const std::string &name, DSATextureType type) {
    glCreateTextures(static_cast<GLenum>(type), 1, &m_id);
    AttachFromFile(name);
}

DSATexture::~DSATexture() {
    Clean();
}

DSATexture &DSATexture::operator=(const std::string &name) {
    AttachFromFile(name);
    return *this;
}

void DSATexture::FromFile(const std::string &) {

}

void DSATexture::AttachFromFile(const std::string &, bool generateMipMap) {

}

void DSATexture::Clean() {
    if (m_id != 0)
    {
        glDeleteTextures(1, &m_id);
        m_id = 0;
    }
}
