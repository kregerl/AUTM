#include "Application.h"

#include <Renderer/RenderSystem.h>
#include <Renderer/Renderer2D.h>
#include <Core/Log.h>

Application* Application::s_instance = nullptr;

Application::Application() {
    s_instance = this;
    m_window = std::make_unique<Window>(WindowProperties());
    m_window->setEventCallback(BIND_EVENT_FUNCTION(Application::onEvent));

    glEnable(GL_DEBUG_OUTPUT);
    Renderer2D::init();
}

Application::~Application() {
    Renderer2D::shutdown();
}

void Application::onEvent(Event& event) {

    // TODO: Add WindowClosed listener and WindowResized listener
    EventDispatcher dispatcher(event);
//    dispatcher.dispatchEvent<KeyPressedEvent>(Input::onKeyPressedEvent);
//    dispatcher.dispatchEvent<KeyReleasedEvent>(Input::onKeyReleasedEvent);
//    dispatcher.dispatchEvent<MouseScrolledEvent>(Input::onMouseScrolledEvent);
//    dispatcher.dispatchEvent<MouseButtonPressedEvent>(BIND_EVENT_FUNCTION(Application::onMouseButtonPressed));
    for (auto it = m_layerStack.end(); it != m_layerStack.begin();) {
        if (event.getEventResult() != EventResult::Pass)
            break;
        (*--it)->onEvent(event);
    }
}

void Application::run() {

    while (!m_window->shouldClose()) {

        m_window->onUpdate();
        m_window->pollEvents();
        glEnable(GL_MULTISAMPLE);

        for (Layer* layer : m_layerStack) {
            layer->onUpdate(m_window->getDeltaTime());
        }

    }

    m_window->close();
}

void Application::pushLayer(Layer* layer) {
    m_layerStack.pushLayer(layer);
    layer->onInit();
}

void Application::pushOverlay(Layer* layer) {
    m_layerStack.pushOverlay(layer);
    layer->onInit();
}
