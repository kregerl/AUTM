#include "Application.h"

#include "Renderer/Texture2D.h"

Application *Application::s_instance = nullptr;

Application::Application() {
    s_instance = this;
    m_window = std::make_unique<Window>(WindowProperties());
    m_shader = std::make_unique<Shader>(R"(C:\Users\kregerl\CLionProjects\Autm\assets\shaders\vertex.glsl)",
                                        R"(C:\Users\kregerl\CLionProjects\Autm\assets\shaders\fragment.glsl)");
    m_cameraController = std::make_unique<OrthographicCameraController>(
            (float) m_window->getWidth() / (float) m_window->getHeight());

    m_window->setEventCallback(BIND_EVENT_FUNCTION(Application::onEvent));

    Texture2D *texture = new Texture2D(R"(C:\Users\kregerl\CLionProjects\Autm\assets\images\play32xwhite.png)");



    // -------------------------------
    // ------------ Quad -------------
    // -------------------------------

    float vertices[] = {
            0.5f, 0.5f, 0.0f, 0.8f, 0.2f, 0.3f, // top right
            0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, // bottom right
            -0.5f, -0.5f, 0.0f, 0.2f, 0.7f, 0.0f, // bottom left
            -0.5f, 0.5f, 0.0f, 0.4f, 0.8f, 0.3f // top left
    };
    unsigned int indices[] = {
            0, 1, 3,  // first Triangle
            1, 2, 3   // second Triangle
    };


    m_quadVA.reset(new VertexArray());
    m_quadVA->bind();

    std::shared_ptr<VertexBuffer> vertexBuffer = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));
    VertexBufferLayout layout = {
            {ShaderDataType::Vec3f, "a_pos",   false},
            {ShaderDataType::Vec3f, "a_color", false},
    };
    vertexBuffer->setLayout(layout);
    m_quadVA->addVertexBuffer(vertexBuffer);

    std::shared_ptr<IndexBuffer> indexBuffer = std::make_shared<IndexBuffer>(indices,
                                                                             sizeof(indices) / sizeof(unsigned int));
    m_quadVA->setIndexBuffer(indexBuffer);

    vertexBuffer->unbind();
    m_quadVA->unbind();

    // -------------------------------
    // ------------ Line -------------
    // -------------------------------

    float lineVerts[] = {
            0.8f, 0.8f, 0.2f, 0.3f, 0.8f, 1.0f,
            0.5f, -0.8f, 0.2f, 0.3f, 0.8f, 1.0f
    };

    unsigned int lineIndices[] = {
            0, 1
    };

    m_lineVA.reset(new VertexArray());
    m_lineVA->bind();

    std::shared_ptr<VertexBuffer> lineVB = std::make_shared<VertexBuffer>(lineVerts, sizeof(lineVerts));
    VertexBufferLayout lineLayout = {
            {ShaderDataType::Vec3f, "a_pos",   false},
            {ShaderDataType::Vec3f, "a_color", false},

    };
    lineVB->setLayout(lineLayout);
    m_lineVA->addVertexBuffer(lineVB);

    std::shared_ptr<IndexBuffer> lineIB = std::make_shared<IndexBuffer>(lineIndices,
                                                                        sizeof(lineIndices) / sizeof(unsigned int));
    m_lineVA->setIndexBuffer(lineIB);

    lineVB->unbind();
    m_lineVA->unbind();


}


void Application::onEvent(Event &event) {
    // Send events to camera controller
    m_cameraController->onEvent(event);

    EventDispatcher dispatcher(event);
    dispatcher.dispatchEvent<KeyPressedEvent>(Input::onKeyPressedEvent);
    dispatcher.dispatchEvent<KeyReleasedEvent>(Input::onKeyReleasedEvent);

}


void Application::run() {

    while (!m_window->shouldClose()) {
        m_window->onUpdate();
        m_window->pollEvents();

        m_cameraController->onUpdate(m_window->getDeltaTime());
        Renderer::clearColor(0.0f, 0.0f, 0.0f, 1.0f);

        m_shader->use();
        m_shader->setMat4("u_viewProjectionMatrix", m_cameraController->getCamera().getViewProjectionMatrix());

        Renderer::draw(m_quadVA);
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        m_quadVA->unbind();

        m_shader->use();
        m_shader->setMat4("u_viewProjectionMatrix", m_cameraController->getCamera().getViewProjectionMatrix());

        glLineWidth(5.0f);
        Renderer::draw(m_lineVA, GL_LINES);
//        glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, nullptr);
        m_lineVA->unbind();


    }

    m_window->close();
}
