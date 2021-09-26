#include "Texture2D.h"

Texture2D::Texture2D(const std::string &path) : m_path(path) {
    int nrChannels;
    unsigned char *data = stbi_load(m_path.c_str(), &m_width, &m_height, &nrChannels, 0);
    m_formats = determineChannels(nrChannels);
    if (data) {
        std::cout << m_formats << std::endl;
    }

    stbi_image_free(data);
}

void Texture2D::bind() {

}

void Texture2D::unbind() {

}

Texture2DFormats Texture2D::determineChannels(int channels) {
    if (channels == 4) {
        return {GL_RGBA8, GL_RGBA};
    } else if (channels == 3) {
        return {GL_RGB8, GL_RGB};
    }
}

