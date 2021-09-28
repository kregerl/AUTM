#ifndef AUTM_TEXTURE2D_H
#define AUTM_TEXTURE2D_H

#include "autmpch.h"
#include <glad/glad.h>
#include <stb_image.h>


/**
 * Holds the formats for a texture
 * < Internal Format, Data Format>
 */
struct Texture2DFormats {
    int channels;
    GLenum internalFormat;
    GLenum dataFormat;

    friend std::ostream &operator<<(std::ostream &os, const Texture2DFormats &formats) {
        os << "Channels: " << formats.channels << "\n" << "Internal Format: " << formats.internalFormat << '\n' << "Data Format: " << formats.dataFormat;
        return os;
    }
};

class Texture2D {
public:
    Texture2D(int width, int height);

    Texture2D(const std::string &path);

    ~Texture2D();

    void bind(int slot = 0);

    void unbind();

    void setData(uint32_t size, void* data);

    int getWidth() const { return m_width; }

    int getHeight() const { return m_height; }

    GLuint getOpenGLId() const { return m_rendererId; }

private:
    Texture2DFormats determineChannels(int channels);

private:
    std::string m_path;
    int m_width, m_height;
    Texture2DFormats m_formats;
    GLuint m_rendererId;

};


#endif
