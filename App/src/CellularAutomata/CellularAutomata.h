#ifndef AUTM_CELLULARAUTOMATA_H
#define AUTM_CELLULARAUTOMATA_H

#include <Autm.h>
#include "Simulations/GameOfLife.h"
#include "Simulations/RuleN.h"
#include "Simulations/SmoothLife.h"

class CellularAutomata : public Layer {
public:
    CellularAutomata();

    ~CellularAutomata() override = default;

    void on_init() override;

    void on_shutdown() override;

    void on_update(float ts) override;

    void on_event(Event& event) override;

    void on_imgui_render() override;

    EventResult on_window_resized(WindowResizedEvent& event);

private:
//    RuleN m_simulation;
//    GameOfLife m_simulation;
    SmoothLife m_simulation;

    bool m_regenerate = true;

    uint32_t m_current_frame = 0;
    // The amount of frames actually displayed on the screen
    uint32_t m_total_displayed_frames = 0;

    OrthographicCamera m_camera;

    std::unique_ptr<Framebuffer> m_previous_framebuffer;
    std::unique_ptr<Framebuffer> m_current_framebuffer;
    glm::vec2 m_viewport_size = {0.0f, 0.0f};
    float m_cell_size = 50.0f;

    std::unique_ptr<Texture2D> m_noise_texture;
    std::shared_ptr<Shader> m_life_shader;
    std::shared_ptr<Shader> m_passthrough_shader;
    std::shared_ptr<VertexArray> m_vertex_array;

};


#endif //AUTM_CELLULARAUTOMATA_H
