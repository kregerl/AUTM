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
};


#endif //AUTM_SMOOTHLIFE_H
