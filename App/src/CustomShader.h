#ifndef AUTM_CUSTOMSHADER_H
#define AUTM_CUSTOMSHADER_H


#include <Core/Layer.h>
#include <Scene/Scene.h>
#include <Renderer/Shader.h>
#include <Renderer/VertexArray.h>
#include <Renderer/Framebuffer.h>

class CustomShader : public Layer {
public:
    CustomShader();

    ~CustomShader() override = default;

    void on_init() override;

    void on_shutdown() override;

    void on_update(float ts) override;

    void on_event(Event& event) override;

    void on_imgui_render() override;

    EventResult on_window_resized(WindowResizedEvent& event);

private:
    OrthographicCameraController m_camera_controller;

    glm::vec2 m_viewport_size = {0.0f, 0.0f};
    std::unique_ptr<Framebuffer> m_framebuffer;

    std::shared_ptr<Texture2D> m_sand_texture;

    std::shared_ptr<Shader> m_shader;
    std::shared_ptr<Shader> m_blur;
    std::shared_ptr<VertexArray> m_quad_va;

};


#endif //AUTM_CUSTOMSHADER_H
