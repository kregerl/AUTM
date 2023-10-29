#ifndef AUTM_RENDERER2D_H
#define AUTM_RENDERER2D_H

#include "autmpch.h"

#include "VertexArray.h"
#include "Shader.h"
#include "OrthographicCameraController.h"
#include "Texture2D.h"
#include "RenderSystem.h"

class Renderer2D {
public:
    static void init();

    static void shutdown();

    static void begin(OrthographicCamera camera);

    static void end();

    static void start_batch();

    static void flush();

    static void draw_quad(const glm::mat4 &transform, const glm::vec4 &color);

    static void draw_quad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color);

    static void draw_quad(const glm::vec3 &position, const glm::vec2 &size, const std::shared_ptr<Texture2D> &texture,
                          float tiling_factor = 1.0f, const glm::vec4 &color = glm::vec4(1.0f));

    static void draw_quad(const glm::mat4 &transform, const std::shared_ptr<Texture2D> &texture,
                          float tiling_factor = 1.0f, const glm::vec4 &color = glm::vec4(1.0f));

    static void draw_rect(const glm::mat4 &transform, const glm::vec4 &color = glm::vec4(1.0f));

    static void draw_rect(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color = glm::vec4(1.0f));

    static void draw_line(const glm::vec3 &position0, const glm::vec3 &position1,
                          const glm::vec4 &color = glm::vec4(1.0f));

/**
 * @param position
 * @param size
 * @param color
 * @param thickness Distance to skip when rendering the inside of the circle. Values < 1 will create a donut
 * @param fade
 */
    static void
    draw_circle_with_radius(const glm::vec3 &position, float radius, const glm::vec4 &color = glm::vec4(1.0f));

    static void draw_circle(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color = glm::vec4(1.0f),
                            float tiling_factor = 1.0f, float thickness = 1.0f, float fade = 0.05f);

    static void draw_circle(const glm::vec3 &position, const glm::vec2 &size, const std::shared_ptr<Texture2D> &texture,
                            const glm::vec4 &color = glm::vec4(1.0f), float tiling_factor = 1.0f,
                            float thickness = 1.0f, float fade = 0.05f);

    static void draw_circle(const glm::mat4 &transform, const std::shared_ptr<Texture2D> &texture,
                            const glm::vec4 &color = glm::vec4(1.0f), float tiling_factor = 1.0f,
                            float thickness = 1.0f, float fade = 0.05f);

    static void draw_circle(const glm::mat4 &transform, const glm::vec4 &color = glm::vec4(1.0f),
                            float tiling_factor = 1.0f, float thickness = 1.0f, float fade = 0.05f);


    static void submit(const std::shared_ptr<Shader> &shader, const std::shared_ptr<VertexArray> &vertex_array,
                       const glm::mat4 &modelMatrix = glm::mat4());

    template<typename Uniforms>
    static void submit_with_uniforms(const std::shared_ptr<Shader> &shader, const std::shared_ptr<VertexArray> &vertex_array,
                Uniforms uniforms) {
        shader->bind();
        vertex_array->bind();
        uniforms();
        RenderSystem::draw(vertex_array);
        vertex_array->unbind();
    }

private:
    static float determine_texture_index(const std::shared_ptr<Texture2D> &texture);

    static void init_quad(const std::shared_ptr<IndexBuffer> &index_buffer);

    static void init_line();

    static void init_circle(const std::shared_ptr<IndexBuffer> &index_buffer);

//    init_quad();
};

#endif