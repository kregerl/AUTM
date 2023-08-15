#ifndef AUTM_TEXTURE2D_H
#define AUTM_TEXTURE2D_H

#include "autmpch.h"
#include <glad/glad.h>
#include <stb_image/stb_image.h>


/**
 * Holds the formats for a texture
 * < Internal Format, Data Format>
 */
struct Texture2DFormats {
    int channels;
    GLenum internal_format;
    GLenum data_formats;
};

class Texture2D {
public:
    Texture2D(int width, int height);

    explicit Texture2D(std::string_view path);

    ~Texture2D();

    void bind(uint32_t slot = 0);

    void unbind();

    void set_data(uint32_t size, void* data);

    int get_width() const { return m_width; }

    int get_height() const { return m_height; }

    GLuint get_opengl_id() const { return m_renderer_id; }

private:
    Texture2DFormats determine_channels(int channels);

private:
    int m_width, m_height;
    Texture2DFormats m_formats;
    GLuint m_renderer_id;

};


#endif
