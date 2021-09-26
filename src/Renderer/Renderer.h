#ifndef AUTM_RENDERER_H
#define AUTM_RENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "VertexArray.h"

class Renderer {
public:


    static void clearColor(glm::vec4 color);

    static void clearColor(float r, float g, float b, float a = 1.0f);

    static void clear(int mask);

    static void draw(std::shared_ptr<VertexArray> &vertexArray, GLenum mode = GL_TRIANGLES, int count = 0);


};


#endif