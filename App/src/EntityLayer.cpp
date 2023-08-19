#include "EntityLayer.h"
#include <App/Application.h>
#include <Scene/Entity.h>
#include <Renderer/Renderer2D.h>
#include <Renderer/RenderSystem.h>
#include <Scene/Components.h>

EntityLayer::EntityLayer() : m_camera_controller(Application::get_instance()->get_window().get_aspect_ratio()) {
    m_active_scene = std::make_unique<Scene>();
    m_sand_texture = std::make_shared<Texture2D>("/home/loucas/CLionProjects/Autm/assets/images/sand.png");

    m_entity = m_active_scene->create_entity();
    m_entity.add_component<SpriteRendererComponent>(m_sand_texture);
    m_entity.add_component<Rigidbody2DComponent>(Rigidbody2DComponent::Type::Dynamic);
    m_entity.add_component<BoxCollider2DComponent>();
}

void EntityLayer::on_update(float ts) {
    m_camera_controller.on_update(ts);

    RenderSystem::clear_color(0.0f, 0.0f, 0.0f, 1.0f);
    Renderer2D::begin(m_camera_controller.get_camera());
    m_active_scene->on_update(ts);
    Renderer2D::draw_quad(glm::vec3(-1.7777778 + 0.5f, 0.0f, 0.0f), glm::vec2(1.0f), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
//    Renderer2D::draw_quad(glm::vec3(0.0f), glm::vec2(1.0f), m_sand_texture, 10.0f);
//    Renderer2D::draw_rect(glm::vec3(1.0f), glm::vec2(1.0f));
//    Renderer2D::draw_line(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(2.0f, 0.0f, 0.0f), glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
//    Renderer2D::draw_circle(glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f), m_sand_texture, glm::vec4(1.0f), 1.5f);
    Renderer2D::end();
}

void EntityLayer::on_init() {
    m_active_scene->begin_physics_runtime();
}

void EntityLayer::on_shutdown() {
    Renderer2D::shutdown();
    m_active_scene->end_physics_runtime();
}

void EntityLayer::on_event(Event& event) {
    m_camera_controller.on_event(event);
}
