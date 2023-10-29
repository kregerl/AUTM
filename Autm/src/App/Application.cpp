#include "Application.h"

#include <Renderer/RenderSystem.h>
#include <Renderer/Renderer2D.h>
#include <Core/Log.h>

Application *Application::s_instance = nullptr;

Application::Application() {
    s_instance = this;
    m_window = std::make_unique<Window>(WindowProperties());
    m_window->set_event_callback(AUTM_BIND(Application::on_event));

    glEnable(GL_DEBUG_OUTPUT);
    Renderer2D::init();

    m_imgui_layer = new ImGuiLayer();
    push_overlay(m_imgui_layer);
}

Application::~Application() {
    Renderer2D::shutdown();
}

void Application::on_event(Event &event) {
    EventDispatcher dispatcher(event);
    dispatcher.dispatch_event<WindowResizedEvent>(AUTM_BIND(Application::on_window_resized));
    dispatcher.dispatch_event<WindowClosedEvent>(AUTM_BIND(Application::on_window_closed));
    for (auto it = m_layerstack.end(); it != m_layerstack.begin();) {
        if (event.get_event_result() != EventResult::Pass)
            break;
        (*--it)->on_event(event);
    }
}

void Application::run() {

    while (m_running) {

        m_window->onUpdate();
        m_window->poll_events();
//        glEnable(GL_MULTISAMPLE);

        auto ts = static_cast<float>(m_window->get_delta_time());
        for (Layer *layer: m_layerstack) {
            layer->on_update(ts);
        }

        m_imgui_layer->begin(ts);
        for (Layer *layer: m_layerstack) {
            layer->on_imgui_render();
        }
        m_imgui_layer->end();
    }
}

void Application::push_layer(Layer *layer) {
    m_layerstack.push_layer(layer);
    layer->on_init();
}

void Application::push_overlay(Layer *layer) {
    m_layerstack.push_overlay(layer);
    layer->on_init();
}

EventResult Application::on_window_resized(WindowResizedEvent &event) {
    auto width = event.get_width();
    auto height = event.get_height();


    if (width == 0 || height == 0) {
//        m_minimized = true;
        return EventResult::Deny;
    }

//    m_minimized = false;
    RenderSystem::set_viewport(0, 0, width, height);
    return EventResult::Pass;
}

EventResult Application::on_window_closed(WindowClosedEvent &event) {
    m_running = false;
    return EventResult::Consume;
}
