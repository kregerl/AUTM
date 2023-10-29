#ifndef AUTM_PHYSICSLAYER_H
#define AUTM_PHYSICSLAYER_H

#include "Autm.h"
#include "autmpch.h"
#include <Physics/PhysicsWorld.h>

class PhysicsLayer : public Layer {
public:
    PhysicsLayer();
    ~PhysicsLayer() = default;

    void on_init() override;

    void on_shutdown() override;

    void on_update(float ts) override;

    void on_imgui_render() override;

    void on_event(Event &event) override;

    EventResult on_mouse_clicked(MouseButtonPressedEvent &);
    EventResult on_mouse_released(MouseButtonReleasedEvent &);
    EventResult on_mouse_moved(MouseMovedEvent &);

private:
    void constrain(Vertex &vertex);

private:
    OrthographicCameraController m_camera_controller;
    std::vector<Vertex> m_positions;

    PhysicsWorld m_physics_world;
    bool m_paused = true;
    bool m_mouse_down = false;
};


#endif //AUTM_PHYSICSLAYER_H
