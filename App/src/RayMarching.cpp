#include <Renderer/RenderSystem.h>
#include <Renderer/Renderer2D.h>
#include <App/Application.h>
#include <glm/ext/matrix_transform.hpp>
#include <Core/Log.h>
#include <Core/KeyCodes.h>
#include "RayMarching.h"

RayMarching::RayMarching() : Layer("Ray Marching"), m_camera(-1.7777778, 1.7777778, 1, -1),
                             m_fake_camera(0.0f, 0.0f, -10.0f) {}

void RayMarching::on_init() {
    m_shader.reset(new Shader(
            "/home/loucas/CLionProjects/Autm/assets/shaders/RayMarchVertex.glsl",
            "/home/loucas/CLionProjects/Autm/assets/shaders/RayMarchFragment.glsl"));

    float vertices[4 * 3] = {
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            1.0f, 1.0f, 0.0f,
            -1.0f, 1.0f, 0.0f
    };
    unsigned int indices[2 * 3] = {
            0, 1, 3,
            1, 2, 3
    };
    m_fsQuadVA = std::make_shared<VertexArray>();
    m_fsQuadVA->bind();
    std::shared_ptr<VertexBuffer> vertexBuffer = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));
    vertexBuffer->set_layout({
                                     {ShaderDataType::Vec3f, "a_pos", false},
                             });
    m_fsQuadVA->add_vertex_buffer(vertexBuffer);
    std::shared_ptr<IndexBuffer> indexBuffer = std::make_shared<IndexBuffer>(indices,
                                                                             sizeof(indices) /
                                                                             sizeof(unsigned int));
    m_fsQuadVA->set_index_buffer(indexBuffer);
}

void RayMarching::on_shutdown() {
}

void RayMarching::on_update(float ts) {
    RenderSystem::clear_color(0.0f, 0.0f, 0.0f, 1.0f);
    Renderer2D::begin(m_camera);

    glm::vec2 resolution = Application::get_instance()->get_window().get_resolution();

    glm::mat4 modelMatrix = glm::scale(glm::mat4(1.0f), {resolution.x, resolution.y, 1.0f});

    m_fsQuadVA->bind();
    m_shader->bind();
    m_shader->set_vec2("u_resolution", resolution);
    m_shader->set_float("u_time", ts);

    Renderer2D::submit(m_shader, m_fsQuadVA, modelMatrix);

    Renderer2D::end();
}

void RayMarching::on_event(Event& event) {
    EventDispatcher dispatcher(event);
    dispatcher.dispatch_event<KeyPressedEvent>(AUTM_BIND_EVENT(RayMarching::on_key_pressed));

    Layer::on_event(event);
}

EventResult RayMarching::on_key_pressed(KeyPressedEvent& event) {
    switch (event.get_keycodes()) {
        case KEY_A: {
            m_fake_camera.x -= 0.5f;
            return EventResult::Consume;
        }
        case KEY_D: {
            m_fake_camera.x += 0.5f;
            return EventResult::Consume;
        }
        default: {
            break;
        }
    }


    return EventResult::Pass;
}
