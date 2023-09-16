#include <imgui/imgui.h>
#include <Renderer/UniformBuffer.h>
#include "RuleN.h"

RuleN::RuleN() {
    m_shader = std::make_shared<Shader>(
            "/home/loucas/CLionProjects/Autm/assets/shaders/CellularAutomata/GenericVertexShader.glsl",
            "/home/loucas/CLionProjects/Autm/assets/shaders/CellularAutomata/RuleNFrag.glsl");
}

const std::shared_ptr<Shader>& RuleN::simulate() {
    m_shader->bind();
    m_shader->set_int("u_rule", m_rule);
    m_shader->unbind();
    return m_shader;
}

void RuleN::on_imgui_render() {
    if (ImGui::Button("Play / Pause", ImVec2(120, 24))) {
        m_paused = !m_paused;
        if (!m_paused)
            m_should_reset = false;
    }

    if (ImGui::Button("Reset", ImVec2(120, 24))) {
        m_paused = true;
        m_should_reset = true;
    }

    ImGuiInputTextFlags_ flags = ImGuiInputTextFlags_None;
    if (!m_paused)
        flags = ImGuiInputTextFlags_ReadOnly;

    ImGui::InputInt("Update Rate", (int*) &m_update_rate, 0, 0, flags);
    ImGui::InputInt("Rule", &m_rule, 0, 0, flags);
}
