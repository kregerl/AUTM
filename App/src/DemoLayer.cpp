#include "DemoLayer.h"
#include <imgui/imgui.h>

void DemoLayer::on_update(float ts) {
    ImGuiLayer::begin(ts);
    static bool show = true;
    ImGui::ShowDemoWindow(&show);
    ImGuiLayer::end();
}
