#include "EntityLayer.h"
#include <Scene/Entity.h>
#include <Renderer/Renderer2D.h>
#include <Renderer/RenderSystem.h>
#include <Scene/Components.h>
#include <App/Application.h>
#include <random>
#include <Core/Log.h>

EntityLayer::EntityLayer() : m_camera_controller(Application::get_instance()->get_window().get_aspect_ratio(), 10.0f) {
    m_active_scene = std::make_unique<Scene>();
    m_sand_texture = std::make_shared<Texture2D>("/home/loucas/CLionProjects/Autm/assets/images/sand.png");


    m_active_scene->set_begin_contact_callback([](Entity& entity0, Entity& entity1) {
        std::mt19937 random;
        std::uniform_real_distribution<float> color(0.0f, 1.0f);
        if (entity0.has_component<CircleRendererComponent>() && entity1.has_component<CircleRendererComponent>()) {
            auto r0 = color(random);
            auto r1 = color(random);
            entity0.get_component<CircleRendererComponent>().color.r = r0;
            entity1.get_component<CircleRendererComponent>().color.r = r1;
        }
    });

    auto size = m_camera_controller.get_camera_size();

    auto enclosing_entity = m_active_scene->create_entity();
    enclosing_entity.add_component<Rigidbody2DComponent>();
    enclosing_entity.add_component<RectCollider2DComponent>();
    auto& transform = enclosing_entity.get_component<TransformComponent>();
    transform.scale = glm::vec3(size.x, size.y, 1.0f);

    auto half_size = size / 2.0f;

    std::mt19937 random;
    std::uniform_real_distribution<float> x_pos(-half_size.x, half_size.x);
    std::uniform_real_distribution<float> y_pos(-half_size.y, half_size.y);

    for (uint32_t i = 0; i < 50; i++) {
        m_entity = m_active_scene->create_entity();
        m_entity.add_component<CircleRendererComponent>(m_sand_texture);
        m_entity.add_component<Rigidbody2DComponent>(Rigidbody2DComponent::Type::Dynamic);
        auto& collider = m_entity.add_component<CircleCollider2DComponent>();
        collider.restitution = 0.5f;
        collider.friction = 0.1f;
        auto& entity_transform = m_entity.get_component<TransformComponent>();
        entity_transform.translation.x = x_pos(random);
        entity_transform.translation.y = y_pos(random);
    }
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
    m_active_scene->begin_simulation();
}

void EntityLayer::on_shutdown() {
    Renderer2D::shutdown();
    m_active_scene->end_simulation();
}

void EntityLayer::on_event(Event& event) {
}
