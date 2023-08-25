#ifndef AUTM_ENTITYLAYER_H
#define AUTM_ENTITYLAYER_H

#include <Core/Layer.h>
#include <Renderer/OrthographicCameraController.h>
#include <Scene/Scene.h>
#include <Renderer/VertexArray.h>
#include <Renderer/Shader.h>
#include <Renderer/Texture2D.h>
#include <Scene/Entity.h>

class EntityLayer : public Layer {
public:
    EntityLayer();

    ~EntityLayer() override = default;

    void on_init() override;

    void on_shutdown() override;

    void on_update(float ts) override;

    void on_event(Event &event) override;
private:
    OrthographicCameraController m_camera_controller;
    std::unique_ptr<Scene> m_active_scene;

    std::shared_ptr<Shader> m_shader;
    std::shared_ptr<Texture2D> m_sand_texture;
    Entity m_entity;

    Entity m_left_entity;
    Entity m_right_entity;
};

#endif //AUTM_ENTITYLAYER_H
