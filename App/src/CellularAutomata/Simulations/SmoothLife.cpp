#include <imgui/imgui.h>
#include "SmoothLife.h"

SmoothLife::SmoothLife() {
    m_shader = std::make_shared<Shader>(
            "/home/loucas/CLionProjects/Autm/assets/shaders/CellularAutomata/GenericVertexShader.glsl",
            "/home/loucas/CLionProjects/Autm/assets/shaders/CellularAutomata/SmoothLifeFrag.glsl");
}

const std::shared_ptr<Shader>& SmoothLife::simulate() {
    m_shader->bind();

    m_shader->set_vec2("u_radius", glm::vec2(m_outer_radius, m_inner_radius));
    m_shader->set_float("u_delta_time", m_delta_time);

    m_shader->set_float("u_b1", m_b1);
    m_shader->set_float("u_b2", m_b2);
    m_shader->set_float("u_d1", m_d1);
    m_shader->set_float("u_d2", m_d2);
    m_shader->set_float("u_alpha_n", m_alpha_n);
    m_shader->set_float("u_alpha_m", m_alpha_m);

    m_shader->unbind();
    return m_shader;
}

void SmoothLife::on_imgui_render() {
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

    const char* format = "%.3f";

    ImGui::SliderFloat("Outer Radius", &m_outer_radius, 0.0f, 40.0f, format, flags);
    ImGui::SliderFloat("Inner Radius", &m_inner_radius, 0.0f, 40.0f, format, flags);

    ImGui::SliderFloat("Delta Time", &m_delta_time, 0.0f, 1.0f, format, flags);
    ImGui::SliderFloat("B1", &m_b1, 0.0f, 1.0f, format, flags);
    ImGui::SliderFloat("B2", &m_b2, 0.0f, 1.0f, format, flags);
    ImGui::SliderFloat("D1", &m_d1, 0.0f, 1.0f, format, flags);
    ImGui::SliderFloat("D2", &m_d2, 0.0f, 1.0f, format, flags);
    ImGui::SliderFloat("Alpha N", &m_alpha_n, 0.0f, 1.0f, format, flags);
    ImGui::SliderFloat("Alpha M", &m_alpha_m, 0.0f, 1.0f, format, flags);


    //    ImGui::ColorEdit3("Color Tint", m_color_tint, ImGuiColorEditFlags_Float);
}

