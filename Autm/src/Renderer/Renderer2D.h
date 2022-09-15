#ifndef AUTM_RENDERER2D_H
#define AUTM_RENDERER2D_H

#include "autmpch.h"

#include "VertexArray.h"
#include "Shader.h"
#include "OrthographicCameraController.h"


class Renderer2D {
public:
    static void init();

    static void shutdown();

    static void begin(OrthographicCamera camera);

    static void end();

    static void drawQuad(glm::vec3 position, glm::vec2 size, float rotation);

    static void drawFractalQuad(glm::vec2 size, glm::vec3 center, glm::vec2 resolution, float iterations);

    static void drawLine(glm::vec3 position, glm::vec2 size, float rotation, float lineWidth);

private:
    static void initQuad();

    static void initFullscreenQuad();

    static void initLine();
};


#endif