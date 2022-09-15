#include <Core/Log.h>
#include "Texture2D.h"

Texture2D::Texture2D(int width, int height) : m_width(width), m_height(height), m_formats({4, GL_RGBA8, GL_RGBA}) {
    glCreateTextures(GL_TEXTURE_2D, 1, &m_rendererId);
    glTextureStorage2D(m_rendererId, 1, m_formats.internalFormat, m_width, m_height);

    glTextureParameteri(m_rendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(m_rendererId, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTextureParameteri(m_rendererId, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(m_rendererId, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

Texture2D::Texture2D(const std::string& path) : m_path(path) {
    int imageChannels;
    unsigned char* data = stbi_load(m_path.c_str(), &m_width, &m_height, &imageChannels, 0);
    m_formats = determineChannels(imageChannels);
    if (data) {
#ifdef DEBUG
        AUTM_CORE_DEBUG("Channels: {}", m_formats.channels);
        AUTM_CORE_DEBUG("Internal Format: {}", m_formats.internalFormat);
        AUTM_CORE_DEBUG("Data Format: {}", m_formats.dataFormat);
#endif
        glCreateTextures(GL_TEXTURE_2D, 1, &m_rendererId);
        glTextureStorage2D(m_rendererId, 1, m_formats.internalFormat, m_width, m_height);

        glTextureParameteri(m_rendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_rendererId, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTextureParameteri(m_rendererId, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_rendererId, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTextureSubImage2D(m_rendererId, 0, 0, 0, m_width, m_height, m_formats.dataFormat, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }

}

Texture2D::~Texture2D() {
    glDeleteTextures(1, &m_rendererId);
}

void Texture2D::bind(int slot) {
    glBindTextureUnit(slot, m_rendererId);
}

void Texture2D::unbind() {
}

void Texture2D::setData(uint32_t size, void* data) {
    int channels = m_formats.channels;
//    assert(size = channels * m_width * m_height);
    glTextureSubImage2D(m_rendererId, 0, 0, 0, m_width, m_height, m_formats.dataFormat, GL_UNSIGNED_BYTE, data);
}

Texture2DFormats Texture2D::determineChannels(int channels) {
    if (channels == 4) {
        return {channels, GL_RGBA8, GL_RGBA};
    } else if (channels == 3) {
        return {channels, GL_RGB8, GL_RGB};
    }
}

