#include <imgui/imgui.h>
#include "SmoothLife.h"

SmoothLife::SmoothLife() {
    m_shader = std::make_shared<Shader>(
            "/home/loucas/CLionProjects/Autm/assets/shaders/CellularAutomata/GenericVertexShader.glsl",
            "/home/loucas/CLionProjects/Autm/assets/shaders/CellularAutomata/SmoothLifeFrag.glsl");
    m_update_rate = 0;
}

const std::shared_ptr<Shader>& SmoothLife::simulate() {
    return m_shader;
}

void SmoothLife::on_imgui_render() {
    ImGui::Begin("Settings");

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
//    ImGui::ColorEdit3("Color Tint", m_color_tint, ImGuiColorEditFlags_Float);

    ImGui::End();
}

