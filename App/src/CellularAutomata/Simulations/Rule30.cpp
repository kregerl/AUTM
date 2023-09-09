#include <imgui/imgui.h>
#include <Renderer/UniformBuffer.h>
#include "Rule30.h"

Rule30::Rule30() {
    m_shader = std::make_shared<Shader>(
            "/home/loucas/CLionProjects/Autm/assets/shaders/CellularAutomata/GenericVertexShader.glsl",
            "/home/loucas/CLionProjects/Autm/assets/shaders/CellularAutomata/Rule30Frag.glsl");
}

const std::shared_ptr<Shader>& Rule30::simulate() {
    const std::vector<int> ruleset = {1, 1, 1, 0,
                                      1, 1, 0, 0,
                                      1, 0, 1, 0,
                                      1, 0, 0, 1,
                                      0, 1, 1, 1,
                                      0, 1, 0, 1,
                                      0, 0, 1, 1,
                                      0, 0, 0, 0};

    auto size = ruleset.size() * sizeof(int);
    auto* buffer = new UniformBuffer(size, 1);
    buffer->set_data(&ruleset[0], size);
    return m_shader;
}

void Rule30::on_imgui_render() {
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

    ImGui::End();
}
