#ifndef AUTM_SIMULATION_H
#define AUTM_SIMULATION_H

#include <Autm.h>

class Simulation {
public:
    virtual const std::shared_ptr<Shader>& simulate() = 0;

    virtual void on_imgui_render() = 0;

    bool is_paused() const { return m_paused; }

    bool should_reset() const { return m_should_reset; }

    uint32_t get_update_rate() const { return m_update_rate; }

protected:
    bool m_paused = true;
    bool m_should_reset = false;
    uint32_t m_update_rate = 0;
};

#endif //AUTM_SIMULATION_H
