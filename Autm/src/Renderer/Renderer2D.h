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

    static void submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray,
                       const glm::mat4& modelMatrix);

    static void drawQuad(glm::vec3 position, glm::vec2 size, float rotation);

    static void drawLine(glm::vec3 position, glm::vec2 size, float rotation, float lineWidth);

private:
    static void initQuad();

    static void initLine();
};


#endif