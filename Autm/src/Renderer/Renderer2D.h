#ifndef AUTM_RENDERER2D_H
#define AUTM_RENDERER2D_H

#include "autmpch.h"

#include "VertexArray.h"
#include "Shader.h"
#include "OrthographicCameraController.h"
#include "Texture2D.h"


class Renderer2D {
public:
    static void init();

    static void shutdown();

    static void begin(OrthographicCamera camera);

    static void end();

    static void flush();

    static void draw_quad(const glm::mat4& transform, const glm::vec4& color);

    static void draw_quad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);

    static void draw_quad(
            const glm::vec3& position,
            const glm::vec2& size,
            const std::shared_ptr<Texture2D>& texture,
            float tiling_factor = 1.0f,
            const glm::vec4& color = glm::vec4(1.0f));

    static void draw_quad(
            const glm::mat4& transform,
            const std::shared_ptr<Texture2D>& texture,
            float tiling_factor = 1.0f,
            const glm::vec4& color = glm::vec4(1.0f));

    static void draw_line(glm::vec3 position, glm::vec2 size, float rotation, float lineWidth);

    static void submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray,
                       const glm::mat4& modelMatrix);

private:
//    init_quad();
};


#endif