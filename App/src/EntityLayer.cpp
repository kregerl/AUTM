#include "EntityLayer.h"
#include <App/Application.h>
#include <Scene/Entity.h>
#include <Renderer/Renderer2D.h>
#include <Renderer/RenderSystem.h>

EntityLayer::EntityLayer() : m_camera_controller(Application::get_instance()->get_window().get_aspect_ratio()) {
    m_active_scene = std::make_unique<Scene>();
    m_sand_texture = std::make_shared<Texture2D>("/home/loucas/CLionProjects/Autm/assets/images/sand.png");
}

void EntityLayer::on_update(float ts) {
    m_camera_controller.on_update(ts);

    m_active_scene->on_update(ts);

    RenderSystem::clear_color(0.0f, 0.0f, 0.0f, 1.0f);
    Renderer2D::begin(m_camera_controller.get_camera());
    Renderer2D::draw_quad(glm::vec3(1.0f), glm::vec2(1.0f), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
    Renderer2D::draw_quad(glm::vec3(0.0f), glm::vec2(1.0f), m_sand_texture, 10.0f);
    Renderer2D::end();
}

void EntityLayer::on_init() {}

void EntityLayer::on_shutdown() {
    Renderer2D::shutdown();
}

void EntityLayer::on_event(Event& event) {
    m_camera_controller.on_event(event);
}
