#include "EntityLayer.h"
#include <Scene/Entity.h>
#include <Renderer/Renderer2D.h>
#include <Renderer/RenderSystem.h>
#include <Scene/Components.h>
#include <App/Application.h>
#include <Core/Log.h>
#include <random>
#include <imgui/imgui.h>

EntityLayer::EntityLayer() : m_camera_controller(Application::get_instance()->get_window().get_aspect_ratio(), 10.0f) {
    m_active_scene = std::make_unique<Scene>();
    m_play_texture = std::make_shared<Texture2D>("/home/loucas/CLionProjects/Autm/assets/images/play32xwhite.png");

    m_gradient.add_color_stop(0.15f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    m_gradient.add_color_stop(0.35f, glm::vec4(0.7f, 0.1f, 0.1f, 1.0f));
    m_gradient.add_color_stop(0.55f, glm::vec4(0.890f, 0.566f, 0.0801f, 1.0f));
    m_gradient.add_color_stop(0.8f, glm::vec4(0.98823529411f, 0.9294117647f, 0.78039215686f, 1.0f));

    m_active_scene->set_continuous_contact_callback([this](Entity& entity0, Entity& entity1, float ts) {
        if (entity0.has_components<TemperatureComponent>() && entity1.has_components<TemperatureComponent>()) {
            auto& entity0_temp = entity0.get_component<TemperatureComponent>();
            auto& entity1_temp = entity1.get_component<TemperatureComponent>();

            if (entity0_temp.temperature == 0.0f && entity1_temp.temperature == 0.0f)
                return;
            auto difference = std::abs(entity0_temp.temperature - entity1_temp.temperature);
            auto transfer = std::min(m_temperature_coefficient * difference * ts, 1.0f);

            if (entity0_temp.temperature > entity1_temp.temperature) {
                entity0_temp.temperature = std::max(entity0_temp.temperature - transfer, 0.0f);
                entity1_temp.temperature = std::min(entity1_temp.temperature + transfer, 1.0f);
            } else {
                entity0_temp.temperature = std::max(entity0_temp.temperature + transfer, 0.0f);
                entity1_temp.temperature = std::min(entity1_temp.temperature - transfer, 1.0f);
            }
        } else if (entity0.has_components<TemperatureComponent>() && entity1.has_components<HeatSourceComponent>()) {
            auto& entity0_temp = entity0.get_component<TemperatureComponent>();
            auto& entity1_temp = entity1.get_component<HeatSourceComponent>();

            if (entity0_temp.temperature == 0.0f && entity1_temp.temperature == 0.0f)
                return;
            entity0_temp.temperature = 1.0f;
        } else if (entity0.has_components<HeatSourceComponent>() && entity1.has_components<TemperatureComponent>()) {
            auto& entity0_temp = entity0.get_component<HeatSourceComponent>();
            auto& entity1_temp = entity1.get_component<TemperatureComponent>();

            if (entity0_temp.temperature == 0.0f && entity1_temp.temperature == 0.0f)
                return;
            entity1_temp.temperature = 1.0f;
        }
    });
    auto camera_size = m_camera_controller.get_camera_size();

    auto size = glm::vec2(camera_size.x / 2.0f, camera_size.y);

    auto enclosing_entity = m_active_scene->create_entity();
    enclosing_entity.add_component<RectRendererComponent>();
    enclosing_entity.add_component<Rigidbody2DComponent>();
    enclosing_entity.add_component<RectCollider2DComponent>();
    auto& transform = enclosing_entity.get_component<TransformComponent>();
    transform.scale = glm::vec3(size.x, size.y, 1.0f);
    auto half_size = size / 2.0f;

    auto heat_entity = m_active_scene->create_entity();
    heat_entity.add_component<Rigidbody2DComponent>();
    heat_entity.add_component<SpriteRendererComponent>();
    heat_entity.add_component<BoxCollider2DComponent>();
    heat_entity.add_component<HeatSourceComponent>();
    auto& heat_transform = heat_entity.get_component<TransformComponent>();
    heat_transform.translation.y = -half_size.y;
    heat_transform.scale = glm::vec3(size.x, 0.25f, 1.0f);

    std::random_device rd;
    std::mt19937 random(rd());
    std::uniform_real_distribution<float> x_pos(-half_size.x, half_size.x);
    std::uniform_real_distribution<float> y_pos(-half_size.y, half_size.y);

    constexpr float scale = 0.25f;
    for (uint32_t i = 0; i < 1000; i++) {
        auto entity = m_active_scene->create_entity();
        entity.add_component<CircleRendererComponent>(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
        entity.add_component<Rigidbody2DComponent>(Rigidbody2DComponent::Type::Dynamic);
        auto& temp = entity.add_component<TemperatureComponent>();
        auto& collider = entity.add_component<CircleCollider2DComponent>();
        collider.restitution = 0.5f;
        collider.friction = 0.1f;
        auto& entity_transform = entity.get_component<TransformComponent>();
        entity_transform.translation.x = x_pos(random);
        entity_transform.translation.y = y_pos(random);
        entity_transform.scale = glm::vec3(scale, scale, 1.0f);
        m_entities.emplace_back(entity);
    }
}

void EntityLayer::on_update(float ts) {
    RenderSystem::clear_color(0.0f, 0.0f, 0.0f, 1.0f);
    Renderer2D::begin(m_camera_controller.get_camera());
    m_active_scene->on_update(ts);

    std::random_device rd;
    std::mt19937 random(rd());
    std::uniform_real_distribution<float> impulse(-2.0f, 8.0f);

    if (!m_active_scene->get_paused()) {
        float average_temp = 0.0f;
        for (auto& entity: m_entities) {
            auto& temp = entity.get_component<TemperatureComponent>();
            float new_temp = temp.temperature - ((m_heat_decay * (0.95f - temp.temperature)) * ts);
            auto& circle = entity.get_component<CircleRendererComponent>();
            if (temp.temperature != 0.0f) {
                auto color = m_gradient.get_color_at(temp.temperature);
                circle.color = glm::vec4(color.r, color.g, color.b, color.a);
            } else {
                circle.color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
            }
            auto& collider = entity.get_component<CircleCollider2DComponent>();
            collider.density = m_density_coefficient * (1.0f - temp.temperature);
            if (temp.temperature > 0.45f)
                m_active_scene->apply_force_by_id(entity.get_component<IdentifierComponent>().id,
                                                  glm::vec2(0.0f, (m_force_coefficient * temp.temperature) +
                                                                  impulse(random)));
            average_temp += temp.temperature;
            temp.temperature = std::max(new_temp, 0.0f);
        }
    }

//    Renderer2D::draw_quad(glm::vec3(-1.7777778 + 0.5f, 0.0f, 0.0f), glm::vec2(1.0f), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
//    Renderer2D::draw_quad(glm::vec3(0.0f), glm::vec2(1.0f), m_sand_texture, 10.0f);
//    Renderer2D::draw_rect(glm::vec3(1.0f), glm::vec2(1.0f));
//    Renderer2D::draw_line(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(2.0f, 0.0f, 0.0f), glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
//    Renderer2D::draw_circle(glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f), m_sand_texture, glm::vec4(1.0f), 1.5f);
    Renderer2D::end();
}

void EntityLayer::on_imgui_render() {
    ImGui::Begin("Settings");

    if (ImGui::ImageButton((void*) (size_t) m_play_texture->get_opengl_id(), ImVec2(32, 32))) {
        m_active_scene->set_paused(!m_active_scene->get_paused());
    }

    ImGui::SliderFloat("Temperature Coefficient", &m_temperature_coefficient, 0.0f, 15.0f);
    ImGui::SliderFloat("Force Coefficient", &m_force_coefficient, 0.0f, 50.0f);
    ImGui::SliderFloat("Density Coefficient", &m_density_coefficient, 0.0f, 10.0f);
    ImGui::SliderFloat("Heat Decay", &m_heat_decay, 0.0f, 2.0f, "%.3f", ImGuiSliderFlags_NoRoundToFormat);

    ImGui::End();
}

void EntityLayer::on_init() {
    m_active_scene->begin_simulation();
}

void EntityLayer::on_shutdown() {
    Renderer2D::shutdown();
    m_active_scene->end_simulation();
}

void EntityLayer::on_event(Event& event) {}