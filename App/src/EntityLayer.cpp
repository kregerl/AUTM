#include "EntityLayer.h"
#include <Scene/Entity.h>
#include <Renderer/Renderer2D.h>
#include <Renderer/RenderSystem.h>
#include <Scene/Components.h>
#include <App/Application.h>

EntityLayer::EntityLayer() : m_camera_controller(Application::get_instance()->get_window().get_aspect_ratio(), 10.0f) {
    m_active_scene = std::make_unique<Scene>();
    m_sand_texture = std::make_shared<Texture2D>("/home/loucas/CLionProjects/Autm/assets/images/sand.png");

    auto test = m_active_scene->create_entity();
    test.add_component<RectRendererComponent>();
    test.add_component<Rigidbody2DComponent>();
    test.add_component<RectCollider2DComponent>();
    auto& transform = test.get_component<TransformComponent>();
    transform.scale = glm::vec3(5.0f, 5.0f, 1.0f);

//    m_left_entity = m_active_scene->create_entity();
//    m_left_entity.add_component<SpriteRendererComponent>(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
//    m_left_entity.add_component<Rigidbody2DComponent>();
//    m_left_entity.add_component<BoxCollider2DComponent>();
//    auto& left_transform = m_left_entity.get_component<TransformComponent>();
//    left_transform.translation = glm::vec3(-3.0f, 0.0f, 0.0f);
//    left_transform.scale = glm::vec3(10.0f, 0.25f, 1.0f);
//    left_transform.rotation.z = glm::radians(-45.0f);
//
//    m_right_entity = m_active_scene->create_entity();
//    m_right_entity.add_component<SpriteRendererComponent>(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
//    m_right_entity.add_component<Rigidbody2DComponent>();
//    m_right_entity.add_component<BoxCollider2DComponent>();
//    auto& right_transform = m_right_entity.get_component<TransformComponent>();
//    right_transform.translation = glm::vec3(3.0f, 0.0f, 0.0f);
//    right_transform.scale = glm::vec3(10.0f, 0.25f, 1.0f);
//    right_transform.rotation.z = glm::radians(45.0f);

    m_entity = m_active_scene->create_entity();
    m_entity.add_component<CircleRendererComponent>(m_sand_texture);
    m_entity.add_component<Rigidbody2DComponent>(Rigidbody2DComponent::Type::Dynamic);
    m_entity.add_component<CircleCollider2DComponent>();
    auto& entity_transform = m_entity.get_component<TransformComponent>();
    entity_transform.translation.y += 4.0f;
}

void EntityLayer::on_update(float ts) {
    RenderSystem::clear_color(0.0f, 0.0f, 0.0f, 1.0f);
    Renderer2D::begin(m_camera_controller.get_camera());
    m_active_scene->on_update(ts);
//    Renderer2D::draw_quad(glm::vec3(-1.7777778 + 0.5f, 0.0f, 0.0f), glm::vec2(1.0f), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
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
}
