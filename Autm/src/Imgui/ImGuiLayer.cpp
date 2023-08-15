#include <App/Application.h>
#include "ImGuiLayer.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"

ImGuiLayer::ImGuiLayer() : Layer("ImGui") {
}

ImGuiLayer::~ImGuiLayer() {
}

void ImGuiLayer::on_init() {
    ImGui::CreateContext();

    auto& io = ImGui::GetIO();
    (void) io;
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

    ImGui_ImplGlfw_InitForOpenGL(Application::get_instance()->get_window().get_opengl_window(), true);
    ImGui_ImplOpenGL3_Init("#version 460 core");
}

void ImGuiLayer::on_shutdown() {
    ImGui_ImplGlfw_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiLayer::on_event(Event& event) {
    auto& io = ImGui::GetIO();
    if (event.is_in_category(EventCategoryMouse) & io.WantCaptureMouse ||
            event.is_in_category(EventCategoryKeyboard) & io.WantCaptureKeyboard) {
        event.set_event_result(EventResult::Consume);
    }
}

void ImGuiLayer::begin(float ts) {
    auto& io = ImGui::GetIO();
    io.DeltaTime = ts;
    Window& window = Application::get_instance()->get_window();
    io.DisplaySize = ImVec2((float) window.get_width(), (float) window.get_height());

    ImGui_ImplGlfw_NewFrame();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();
}

void ImGuiLayer::end() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
