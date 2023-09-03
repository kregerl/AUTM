#ifndef AUTM_RAYMARCHING_H
#define AUTM_RAYMARCHING_H

#include <Core/Layer.h>
#include <Renderer/OrthographicCamera.h>
#include <Renderer/Shader.h>
#include <Renderer/VertexArray.h>

class RayMarching : public Layer {
public:
    RayMarching();

    ~RayMarching() = default;

    void on_init() override;

    void on_shutdown() override;

    void on_update(float ts) override;

    void on_event(Event& event) override;
private:
    EventResult on_key_pressed(KeyPressedEvent& event);

private:
    OrthographicCamera m_camera;

    std::shared_ptr<Shader> m_shader;
    std::shared_ptr<VertexArray> m_fsQuadVA; // fullscreen quad

    glm::vec3 m_fake_camera;
};


#endif //AUTM_RAYMARCHING_H
