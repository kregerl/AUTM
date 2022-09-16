#ifndef AUTM_RENDERSYSTEM_H
#define AUTM_RENDERSYSTEM_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "VertexArray.h"

class RenderSystem {
public:
    static void clearColor(glm::vec4 color);

    static void clearColor(float r, float g, float b, float a = 1.0f);

    static void clear(int mask);

    static void draw(const std::shared_ptr<VertexArray> &vertexArray, GLenum mode = GL_TRIANGLES, int count = 0);
};


#endif