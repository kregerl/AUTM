#include "Application.h"

#include <Renderer/RenderSystem.h>
#include <Renderer/Renderer2D.h>
#include <Core/Log.h>

Application* Application::s_instance = nullptr;

Application::Application() {
    s_instance = this;
    m_window = std::make_unique<Window>(WindowProperties());
    m_window->setEventCallback(BIND_EVENT_FUNCTION(Application::onEvent));

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

//EventResult Application::onMouseButtonPressed(MouseButtonPressedEvent& event) {
//    if (event.getMouseButton() == L_MOUSE_BUTTON) {
//        auto pos = event.getMousePos();
//        glm::vec2 resolution = m_window->getResolution();
//        float zoom = Input::getScroll();
//        m_center = {
//                m_center.x + (pos.x - (0.5 * resolution.x)) * (4 / resolution.x) * (16 / (9 * zoom)),
//                m_center.y - (pos.y - (0.5 * resolution.y)) * (4 / resolution.y) * (1 / zoom),
//                zoom
//        };
//    }
//}

void Application::run() {

    while (!m_window->shouldClose()) {

        m_window->onUpdate();
        m_window->pollEvents();
        glEnable(GL_MULTISAMPLE);

        for (Layer* layer : m_layerStack) {
            layer->onUpdate(m_window->getDeltaTime());
        }



//        m_cameraController->onUpdate(m_window->getDeltaTime());
//        RenderSystem::clearColor(0.0f, 1.0f, 0.0f, 1.0f);
//        Renderer2D::begin(m_cameraController->getCamera());
//
//        Renderer2D::drawQuad(glm::vec3(0.0f), glm::vec2(0.5f), 0.0f);
//
//        Renderer2D::end();
//
//        RenderSystem::clearColor(0.0f, 1.0f, 0.0f, 1.0f);
//        Renderer2D::begin(m_cameraController->getCamera());


//        float zoom = Input::getScroll();
//        m_center.z = zoom;
//        glm::vec2 size = m_cameraController->getCameraSize();
//        glm::vec2 resolution = m_window->getResolution();


//        Renderer2D::drawFractalQuad(size, m_center, resolution, 1000);

//        Renderer2D::end();
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
