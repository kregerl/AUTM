#ifndef AUTM_RULEN_H
#define AUTM_RULEN_H


#include "../Simulation.h"

class RuleN : public Simulation {
public:
    RuleN();

    ~RuleN() = default;

    const std::shared_ptr<Shader>& simulate() override;

    void on_imgui_render() override;

private:
    std::shared_ptr<Shader> m_shader;
    int m_rule = 90;
};


#endif //AUTM_RULEN_H
