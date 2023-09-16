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
};


#endif //AUTM_SMOOTHLIFE_H
