#ifndef AUTM_SLIMEMOLDSIMULATION_H
#define AUTM_SLIMEMOLDSIMULATION_H


#include "Core/Layer.h"
#include "Autm.h"

class SlimeMoldSimulation : public Layer {
public:
    SlimeMoldSimulation();

    ~SlimeMoldSimulation() override = default;

    void on_init() override;

    void on_shutdown() override;

    void on_update(float ts) override;

    void on_event(Event &event) override;

private:
    OrthographicCamera m_camera;

    std::unique_ptr<Texture2D> m_texture;
//    std::unique_ptr<Framebuffer> m_previous_framebuffer;
//    std::unique_ptr<Framebuffer> m_current_framebuffer;
    glm::vec2 m_viewport_size = {0.0f, 0.0f};

    std::shared_ptr<ComputeShader> m_simulation_shader;
    std::shared_ptr<Shader> m_passthrough_shader;
    std::shared_ptr<VertexArray> m_vertex_array;

};


#endif //AUTM_SLIMEMOLDSIMULATION_H
