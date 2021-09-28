#include "Application.h"

#include "Renderer/RenderSystem.h"
#include "Renderer/Renderer2D.h"

Application *Application::s_instance = nullptr;

Application::Application() {
    s_instance = this;
    m_window = std::make_unique<Window>(WindowProperties());
    m_cameraController = std::make_unique<OrthographicCameraController>(
            (float) m_window->getWidth() / (float) m_window->getHeight());

    m_window->setEventCallback(BIND_EVENT_FUNCTION(Application::onEvent));

    Renderer2D::init();
}


void Application::onEvent(Event &event) {
    // Send events to camera controller
#ifdef DEBUG
//    std::cout << event << std::endl;
#endif
    m_cameraController->onEvent(event);

    EventDispatcher dispatcher(event);
    dispatcher.dispatchEvent<KeyPressedEvent>(Input::onKeyPressedEvent);
    dispatcher.dispatchEvent<KeyReleasedEvent>(Input::onKeyReleasedEvent);

}

void Application::run() {

    while (!m_window->shouldClose()) {
        m_window->onUpdate();
        m_window->pollEvents();

        glEnable(GL_MULTISAMPLE);

        m_cameraController->onUpdate(m_window->getDeltaTime());

        Renderer2D::begin(m_cameraController->getCamera());
        RenderSystem::clearColor(0.0f, 0.0f, 0.0f, 1.0f);

        Renderer2D::drawQuad(glm::vec3(0.0f), glm::vec2(0.5f, 0.5f), 0.0f);
        Renderer2D::drawLine(glm::vec3(0.0f), glm::vec2(1.0f), 77.0f, 5.0f);

        Renderer2D::end();

    }

    m_window->close();
}
