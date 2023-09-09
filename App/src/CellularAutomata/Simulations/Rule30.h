#ifndef AUTM_RULE30_H
#define AUTM_RULE30_H


#include "../Simulation.h"

class Rule30 : public Simulation {
public:
    Rule30();

    ~Rule30() = default;

    const std::shared_ptr<Shader>& simulate() override;

    void on_imgui_render() override;

private:
    std::shared_ptr<Shader> m_shader;
};


#endif //AUTM_RULE30_H
