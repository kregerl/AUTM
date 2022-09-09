#include "Application.h"

#include <Renderer/RenderSystem.h>
#include <Renderer/Renderer2D.h>
#include <Core/KeyCodes.h>
#include <Core/Log.h>

Application* Application::s_instance = nullptr;

Application::Application() {
    s_instance = this;
    m_window = std::make_unique<Window>(WindowProperties());
    m_cameraController = std::make_unique<OrthographicCameraController>(
            (float) m_window->getWidth() / (float) m_window->getHeight());

    m_window->setEventCallback(BIND_EVENT_FUNCTION(Application::onEvent));

//    m_cameraController->disableInputs();
    Renderer2D::init();
}


void Application::onEvent(Event& event) {
    // Send events to camera controller
#ifdef DEBUG
    AUTM_DEBUG("{}", event);
#endif
    m_cameraController->onEvent(event);

    EventDispatcher dispatcher(event);
    dispatcher.dispatchEvent<KeyPressedEvent>(Input::onKeyPressedEvent);
    dispatcher.dispatchEvent<KeyReleasedEvent>(Input::onKeyReleasedEvent);
    dispatcher.dispatchEvent<MouseScrolledEvent>(Input::onMouseScrolledEvent);
    dispatcher.dispatchEvent<MouseButtonPressedEvent>(BIND_EVENT_FUNCTION(Application::onMouseButtonPressed));

    for (auto it = m_layerStack.end(); it != m_layerStack.begin();) {
        (*--it)->onEvent(event);
//        if (event.isHandled()) {
//            break;
//        }
    }
}

void Application::onMouseButtonPressed(MouseButtonPressedEvent& event) {
    if (event.getMouseButton() == L_MOUSE_BUTTON) {
        auto pos = event.getMousePos();
        glm::vec2 resolution = m_window->getResolution();
        float zoom = Input::getScroll();
        m_center = {
                m_center.x + (pos.x - (0.5 * resolution.x)) * (4 / resolution.x) * (16 / (9 * zoom)),
                m_center.y - (pos.y - (0.5 * resolution.y)) * (4 / resolution.y) * (1 / zoom),
                zoom
        };
    }
}

void Application::run() {

    AUTM_CORE_DEBUG("Before Run loop");
    while (!m_window->shouldClose()) {
        m_window->onUpdate();
        m_window->pollEvents();

        glEnable(GL_MULTISAMPLE);

        m_cameraController->onUpdate(m_window->getDeltaTime());

        RenderSystem::clearColor(0.0f, 1.0f, 0.0f, 1.0f);
        Renderer2D::begin(m_cameraController->getCamera());

        for (Layer* layer : m_layerStack) {
            layer->onUpdate();
        }

        float zoom = Input::getScroll();
        m_center.z = zoom;
        glm::vec2 size = m_cameraController->getCameraSize();
        glm::vec2 resolution = m_window->getResolution();

        Renderer2D::drawFractalQuad(size, m_center, resolution, 100);
        AUTM_CORE_DEBUG(glGetError());

//        Renderer2D::drawQuad({0.0, 0.0, 0.0}, {20, 20}, 45);
        Renderer2D::end();
    }

    m_window->close();
}