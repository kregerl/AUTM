#include "SlimeMoldSimulation.h"
#include "Util/Primitives.h"


SlimeMoldSimulation::SlimeMoldSimulation() : m_camera(Application::get_window().get_aspect_ratio()) {
    m_vertex_array = Primitives::generate_fullscreen_quad(Application::get_window().get_aspect_ratio());

    m_passthrough_shader = std::make_shared<Shader>(
            "/home/loucas/CLionProjects/autm/assets/shaders/core/PassthroughVert.glsl",
            "/home/loucas/CLionProjects/autm/assets/shaders/core/PassthroughFrag.glsl");

    m_simulation_shader = std::make_shared<ComputeShader>(
            "/home/loucas/CLionProjects/autm/assets/shaders/SlimeMoldComputeShader.glsl");

    m_texture = std::make_unique<Texture2D>(512, 512);
}

void SlimeMoldSimulation::on_init() {

}

void SlimeMoldSimulation::on_shutdown() {
    Layer::on_shutdown();
}

void SlimeMoldSimulation::on_update(float ts) {

    unsigned int texture;

    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, 512, 512, 0, GL_RGBA, GL_FLOAT, NULL);

    glBindImageTexture(0, texture, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    RenderSystem::clear_color(0.0f, 0.0f, 0.0f);
    Renderer2D::begin(m_camera);

    m_simulation_shader->bind();
    ComputeShader::dispatch(512, 512, 1);
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);


    m_passthrough_shader->bind();
    m_passthrough_shader->set_vec3("u_color", glm::vec3(1.0f));
    m_passthrough_shader->set_vec3("u_background_color", glm::vec3(0.0f));
    Renderer2D::submit(m_passthrough_shader, m_vertex_array);

    Renderer2D::end();

}

void SlimeMoldSimulation::on_event(Event &event) {
    Layer::on_event(event);
}
