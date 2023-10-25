#include <Renderer/RenderSystem.h>
#include <Renderer/Renderer2D.h>
#include <App/Application.h>
#include <Util/Primitives.h>
#include "RayMarching.h"

RayMarching::RayMarching() : Layer("Ray Marching"), m_camera(Application::get_window().get_aspect_ratio()) {
}

void RayMarching::on_init() {
    m_shader.reset(new Shader(
            "/home/loucas/CLionProjects/autm/assets/shaders/RayMarchVertex.glsl",
            "/home/loucas/CLionProjects/autm/assets/shaders/RayMarchFragment.glsl"));

    m_vertex_array = Primitives::generate_fullscreen_quad(Application::get_window().get_aspect_ratio());
}

void RayMarching::on_shutdown() {
}

void RayMarching::on_update(float ts) {
    RenderSystem::clear_color(0.0f, 0.0f, 0.0f, 1.0f);
    Renderer2D::begin(m_camera);

    glm::vec2 resolution = Application::get_window().get_resolution();

    m_shader->bind();
    m_shader->set_vec2("u_resolution", resolution);
    m_shader->set_float("u_time", ts);

    Renderer2D::submit(m_shader, m_vertex_array);

    Renderer2D::end();
}

void RayMarching::on_event(Event& event) {
    Layer::on_event(event);
}