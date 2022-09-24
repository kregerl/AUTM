#include "DemoLayer.h"
#include <imgui/imgui.h>

void DemoLayer::onUpdate(float ts) {
    ImGuiLayer::begin(ts);
    static bool show = true;
    ImGui::ShowDemoWindow(&show);
    ImGuiLayer::end();
}
