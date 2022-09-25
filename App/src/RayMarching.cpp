#include <Renderer/RenderSystem.h>
#include <Renderer/Renderer2D.h>
#include <App/Application.h>
#include <glm/ext/matrix_transform.hpp>
#include "RayMarching.h"

RayMarching::RayMarching() : Layer("Ray Marching"), m_camera(-1.7777778, 1.7777778, 1, -1) {
}

void RayMarching::onInit() {
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
    vertexBuffer->setLayout({
                                    {ShaderDataType::Vec3f, "a_pos", false},
                            });
    m_fsQuadVA->addVertexBuffer(vertexBuffer);
    std::shared_ptr<IndexBuffer> indexBuffer = std::make_shared<IndexBuffer>(indices,
                                                                             sizeof(indices) /
                                                                             sizeof(unsigned int));
    m_fsQuadVA->setIndexBuffer(indexBuffer);
}

void RayMarching::onShutdown() {
}

void RayMarching::onUpdate(float ts) {
    RenderSystem::clearColor(0.0f, 0.0f, 0.0f, 1.0f);
    Renderer2D::begin(m_camera);

    glm::vec2 resolution = Application::getInstance()->getWindow().getResolution();

    glm::mat4 modelMatrix = glm::scale(glm::mat4(1.0f), {resolution.x, resolution.y, 1.0f});

    m_fsQuadVA->bind();
    m_shader->bind();
    m_shader->setVec2("u_resolution", resolution);

    Renderer2D::submit(m_shader, m_fsQuadVA, modelMatrix);

    Renderer2D::end();
}

void RayMarching::onEvent(Event& event) {
    Layer::onEvent(event);
}
