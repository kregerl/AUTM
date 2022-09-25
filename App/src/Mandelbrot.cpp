#include "Mandelbrot.h"

#include <glm/ext/matrix_transform.hpp>

#include <Renderer/RenderSystem.h>
#include <Renderer/Renderer2D.h>
#include <Core/Log.h>
#include <Core/KeyCodes.h>
#include <App/Application.h>

Mandelbrot::Mandelbrot() : Layer("Mandelbrot"),
                           m_camera(-1.7777778, 1.7777778, 1, -1) {
}

void Mandelbrot::onInit() {
    m_fractalShader.reset(new Shader(
            "/home/loucas/CLionProjects/Autm/assets/shaders/FractalVertex.glsl",
            "/home/loucas/CLionProjects/Autm/assets/shaders/FractalFragment.glsl"));

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
    vertexBuffer->setLayout({
                                    {ShaderDataType::Vec3f, "a_pos", false},
                            });
    m_fsQuadVA->addVertexBuffer(vertexBuffer);
    std::shared_ptr<IndexBuffer> indexBuffer = std::make_shared<IndexBuffer>(indices,
                                                                             sizeof(indices) /
                                                                             sizeof(unsigned int));
    m_fsQuadVA->setIndexBuffer(indexBuffer);
}

void Mandelbrot::onShutdown() {
}

void Mandelbrot::onUpdate(float ts) {

    RenderSystem::clearColor(0.0f, 0.0f, 0.0f, 1.0f);
    Renderer2D::begin(m_camera);

    glm::vec2 resolution = Application::getInstance()->getWindow().getResolution();

    glm::mat4 modelMatrix = glm::scale(glm::mat4(1.0f), {resolution.x, resolution.y, 1.0f});

    m_fsQuadVA->bind();
    m_fractalShader->bind();
    m_fractalShader->setVec3("u_center", glm::vec3(m_center.x, m_center.y, m_zoom));
    m_fractalShader->setVec2("u_resolution", resolution);
    m_fractalShader->setFloat("u_iterations", 100.0f);

    Renderer2D::submit(m_fractalShader, m_fsQuadVA, modelMatrix);

    Renderer2D::end();
}

void Mandelbrot::onEvent(Event& event) {
    EventDispatcher dispatcher(event);
    dispatcher.dispatchEvent<MouseButtonPressedEvent>(AUTM_BIND_EVENT(Mandelbrot::onMouseButtonPressed));
    dispatcher.dispatchEvent<MouseScrolledEvent>(AUTM_BIND_EVENT(Mandelbrot::onMouseScroll));
}

EventResult Mandelbrot::onMouseButtonPressed(MouseButtonPressedEvent& event) {
    if (event.getMouseButton() == L_MOUSE_BUTTON) {
        auto pos = event.getMousePos();
        glm::vec2 resolution = Application::getInstance()->getWindow().getResolution();
//        float zoom = Input::getScroll();
        m_center = {
                m_center.x + (pos.x - (0.5 * resolution.x)) * (4 / resolution.x) * (16 / (9 * m_zoom)),
                m_center.y - (pos.y - (0.5 * resolution.y)) * (4 / resolution.y) * (1 / m_zoom),
        };
        return EventResult::Consume;
    }
    return EventResult::Pass;
}

EventResult Mandelbrot::onMouseScroll(MouseScrolledEvent& event) {
    m_zoom += m_zoom * 0.5f * event.getMouseOffsetY();
    return EventResult::Consume;
}