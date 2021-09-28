#ifndef AUTM_RENDERER2D_H
#define AUTM_RENDERER2D_H

#include "autmpch.h"

#include "VertexArray.h"
#include "Shader.h"
#include "OrthographicCamera.h"


class Renderer2D {
public:
    static void init();

    static void shutdown();

    static void begin(OrthographicCamera camera);

    static void end();

    static void drawQuad(glm::vec3 position, glm::vec2 size, float rotation);

    static void drawLine(glm::vec3 position, glm::vec2 size, float rotation, float lineWidth);

};


#endif