#ifndef AUTM_RENDERSYSTEM_H
#define AUTM_RENDERSYSTEM_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "VertexArray.h"

class RenderSystem {
public:
    static void set_viewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

    static void clear_color(glm::vec4 color);

    static void clear_color(glm::vec3 color);

    static void clear_color(float r, float g, float b, float a = 1.0f);

    static void clear(int mask);

    static void set_line_width(float line_width);

    static void
    draw(const std::shared_ptr<VertexArray>& vertex_array, GLenum mode = GL_TRIANGLES, uint32_t index_count = 0);

    static void draw_indexed(const std::shared_ptr<VertexArray>& vertex_array, uint32_t index_count = 0);

    static void draw_lines(const std::shared_ptr<VertexArray>& vertex_array, uint32_t vertex_count = 0);
};


#endif