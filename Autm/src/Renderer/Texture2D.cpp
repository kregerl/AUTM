#include "Texture2D.h"

#ifdef DEBUG

#include <Core/Log.h>

#endif

Texture2D::Texture2D(uint32_t renderer_id, int width, int height) : m_renderer_id(renderer_id), m_width(width),
                                                                    m_height(height),
                                                                    m_formats({4, GL_RGBA8, GL_RGBA}) {
    glCreateTextures(GL_TEXTURE_2D, 1, &m_renderer_id);
    glTextureStorage2D(m_renderer_id, 1, m_formats.internal_format, m_width, m_height);

    glTextureParameteri(m_renderer_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(m_renderer_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTextureParameteri(m_renderer_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(m_renderer_id, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

Texture2D::Texture2D(int width, int height) : Texture2D(0, width, height) {}

Texture2D::Texture2D(std::string_view path) {
    int imageChannels;
    unsigned char* data = stbi_load(path.data(), &m_width, &m_height, &imageChannels, 0);
    m_formats = determine_channels(imageChannels);
    if (data) {
#ifdef DEBUG
        AUTM_CORE_DEBUG("Channels: {}", m_formats.channels);
        AUTM_CORE_DEBUG("Internal Format: {}", m_formats.internal_format);
        AUTM_CORE_DEBUG("Data Format: {}", m_formats.data_formats);
#endif
        glCreateTextures(GL_TEXTURE_2D, 1, &m_renderer_id);
        glTextureStorage2D(m_renderer_id, 1, m_formats.internal_format, m_width, m_height);

        glTextureParameteri(m_renderer_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_renderer_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTextureParameteri(m_renderer_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_renderer_id, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTextureSubImage2D(m_renderer_id, 0, 0, 0, m_width, m_height, m_formats.data_formats, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }

}

Texture2D::~Texture2D() {
    glDeleteTextures(1, &m_renderer_id);
}

void Texture2D::bind(uint32_t slot) {
    glActiveTexture(GL_TEXTURE0);
    glBindTextureUnit(slot, m_renderer_id);
}

void Texture2D::unbind(uint32_t slot) {
    glBindTextureUnit(slot, 0);
}

void Texture2D::set_data(uint32_t size, void* data) {
    int channels = m_formats.channels;
//    assert(size = channels * m_width * m_height);
    glTextureSubImage2D(m_renderer_id, 0, 0, 0, m_width, m_height, m_formats.data_formats, GL_UNSIGNED_BYTE, data);
}

Texture2DFormats Texture2D::determine_channels(int channels) {
    if (channels == 4) {
        return {channels, GL_RGBA8, GL_RGBA};
    } else if (channels == 3) {
        return {channels, GL_RGB8, GL_RGB};
    }
}


