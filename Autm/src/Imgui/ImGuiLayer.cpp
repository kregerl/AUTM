#include <App/Application.h>
#include "ImGuiLayer.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"

ImGuiLayer::ImGuiLayer() : Layer("ImGui") {
}

ImGuiLayer::~ImGuiLayer() {
}

void ImGuiLayer::onInit() {
    ImGui::CreateContext();

    auto& io = ImGui::GetIO();
    (void) io;
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

    ImGui_ImplGlfw_InitForOpenGL(Application::getInstance()->getWindow().getOpenglWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 460 core");
}

void ImGuiLayer::onShutdown() {
    ImGui_ImplGlfw_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiLayer::onEvent(Event& event) {
    auto& io = ImGui::GetIO();
    if (event.isInCategory(EventCategoryMouse) & io.WantCaptureMouse ||
        event.isInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard) {
        event.setEventResult(EventResult::Consume);
    }
}

void ImGuiLayer::begin(float ts) {
    auto& io = ImGui::GetIO();
    io.DeltaTime = ts;
    Window& window = Application::getInstance()->getWindow();
    io.DisplaySize = ImVec2((float) window.getWidth(), (float) window.getHeight());

    ImGui_ImplGlfw_NewFrame();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();
}

void ImGuiLayer::end() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
