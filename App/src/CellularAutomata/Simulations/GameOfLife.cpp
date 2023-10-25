#include <imgui/imgui.h>
#include "GameOfLife.h"

GameOfLife::GameOfLife() {
    m_shader = std::make_shared<Shader>(
            "/home/loucas/CLionProjects/autm/assets/shaders/CellularAutomata/GenericVertexShader.glsl",
            "/home/loucas/CLionProjects/autm/assets/shaders/CellularAutomata/GameOfLifeFrag.glsl");
    m_update_rate = 10;
}

const std::shared_ptr<Shader>& GameOfLife::simulate() {
    m_shader->bind();
    m_shader->set_float("u_board_size", m_board_size);
    return m_shader;
}

void GameOfLife::on_imgui_render() {
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

    ImGui::InputFloat("Board Size", &m_board_size, 0, 0, nullptr, flags);
    ImGui::InputInt("Update Rate", (int*) &m_update_rate, 0, 0, flags);
//    ImGui::ColorEdit3("Color Tint", m_color_tint, ImGuiColorEditFlags_Float);
}
