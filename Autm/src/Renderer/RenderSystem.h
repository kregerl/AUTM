#ifndef AUTM_RENDERSYSTEM_H
#define AUTM_RENDERSYSTEM_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "VertexArray.h"

class RenderSystem {
public:
    static void clear_color(glm::vec4 color);

    static void clear_color(float r, float g, float b, float a = 1.0f);

    static void clear(int mask);

    static void draw(const std::shared_ptr<VertexArray> &vertex_array, GLenum mode = GL_TRIANGLES, uint32_t index_count = 0);

    static void draw_indexed(const std::shared_ptr<VertexArray> &vertex_array, uint32_t index_count = 0);
};


#endif