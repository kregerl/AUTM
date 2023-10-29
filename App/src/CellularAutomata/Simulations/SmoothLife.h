#ifndef AUTM_SMOOTHLIFE_H
#define AUTM_SMOOTHLIFE_H

#include "../Simulation.h"

class SmoothLife : public Simulation {
public:
    SmoothLife();

    ~SmoothLife() = default;

    const std::shared_ptr<Shader>& simulate() override;

    void on_imgui_render() override;

private:
    std::shared_ptr<Shader> m_shader;

    float m_outer_radius = 9.0f;
    float m_inner_radius = 3.0f;

    float m_delta_time = 0.3f;

    float m_b1 = 0.257f;
    float m_b2 = 0.336f;
    float m_d1 = 0.365f;
    float m_d2 = 0.549f;
    float m_alpha_n = 0.028f;
    float m_alpha_m = 0.147f;
};


#endif //AUTM_SMOOTHLIFE_H
