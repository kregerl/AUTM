#include "Mandelbrot.h"

#include <Renderer/RenderSystem.h>
#include <Renderer/Renderer2D.h>
#include <Core/Log.h>

Mandelbrot::Mandelbrot() : Layer("Mandelbrot"),
                           m_camera(-1.7777778, 1.7777778, 1, -1) {
}

void Mandelbrot::onInit() {
}

void Mandelbrot::onShutdown() {
}

void Mandelbrot::onUpdate(float ts) {

    RenderSystem::clearColor(0.0f, 0.0f, 0.0f, 1.0f);
    Renderer2D::begin(m_camera);

    Renderer2D::drawQuad(glm::vec3(0.0f), glm::vec2(0.5f), 0.0f);

    Renderer2D::end();
}

void Mandelbrot::onEvent(Event& event) {
    EventDispatcher dispatcher(event);
    dispatcher.dispatchEvent<MouseButtonPressedEvent>(BIND_EVENT_FUNCTION(Mandelbrot::onMouseButtonPressed));
}

EventResult Mandelbrot::onMouseButtonPressed(MouseButtonPressedEvent& event) {
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
    return EventResult::Pass;
}
