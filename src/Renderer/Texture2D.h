#ifndef AUTM_TEXTURE2D_H
#define AUTM_TEXTURE2D_H

#include "autmpch.h"
#include <glad/glad.h>
#include <stb_image.h>

struct Texture2DFormats {
    GLenum internalFormat;
    GLenum dataFormat;

    friend std::ostream &operator<<(std::ostream &os, const Texture2DFormats &formats) {
        os << "Internal Format: " << formats.internalFormat << '\n' << "Data Format: " << formats.dataFormat;
        return os;
    }
};

class Texture2D {
public:
    Texture2D(const std::string &path);

    void bind();

    void unbind();

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
