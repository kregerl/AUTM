#ifndef AUTM_ENTITYLAYER_H
#define AUTM_ENTITYLAYER_H

#include <Core/Layer.h>
#include <Renderer/OrthographicCameraController.h>
#include <Scene/Scene.h>
#include <Renderer/VertexArray.h>
#include <Renderer/Shader.h>
#include <Renderer/Texture2D.h>
#include <Scene/Entity.h>
#include <Util/Gradient.h>
#include <Renderer/Framebuffer.h>

class EntityLayer : public Layer {
public:
    EntityLayer();

    ~EntityLayer() override = default;

    void on_init() override;

    void on_shutdown() override;

    void on_update(float ts) override;

    void on_event(Event& event) override;

    void on_imgui_render() override;

    EventResult on_window_resized(WindowResizedEvent& event);

private:
    OrthographicCameraController m_camera_controller;
    OrthographicCamera m_static_camera;
    Gradient m_gradient;

    std::vector<Entity> m_entities;
    std::unique_ptr<Scene> m_active_scene;

    std::shared_ptr<Shader> m_blur;
    std::shared_ptr<VertexArray> m_quad_va;
    std::shared_ptr<Framebuffer> m_framebuffer;
    glm::vec2 m_viewport_size = {0.0f, 0.0f};

    std::shared_ptr<Texture2D> m_sand_texture;
    std::shared_ptr<Texture2D> m_play_texture;

    float m_temperature_coefficient = 1.5f;
    float m_force_coefficient = 5.15f;
    float m_density_coefficient = 6.0f;
    float m_heat_decay = 0.125f;

    struct TemperatureComponent {
        float temperature = 0.0f;

        TemperatureComponent() = default;

        TemperatureComponent(const TemperatureComponent&) = default;
    };

    struct HeatSourceComponent {
        float temperature = 1.0f;

        HeatSourceComponent() = default;

        HeatSourceComponent(const HeatSourceComponent&) = default;
    };

};

#endif //AUTM_ENTITYLAYER_H
