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

    static void start_batch();

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

    static void draw_rect(const glm::mat4& transform, const glm::vec4& color = glm::vec4(1.0f));

    static void draw_rect(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color = glm::vec4(1.0f));

    static void draw_line(
            const glm::vec3& position0,
            const glm::vec3& position1,
            const glm::vec4& color = glm::vec4(1.0f));

    static void submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray,
                       const glm::mat4& modelMatrix);

private:

    static void init_quad();

    static void init_line();
//    init_quad();
};


#endif