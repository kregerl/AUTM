#ifndef AUTM_APPLICATION_H
#define AUTM_APPLICATION_H

#include <Imgui/ImGuiLayer.h>
#include "autmpch.h"
#include "Core/LayerStack.h"
#include "Core/Window.h"
#include "Event/MouseEvents.h"
#include "Event/KeyEvents.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/OrthographicCamera.h"
#include "Renderer/OrthographicCameraController.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture2D.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/VertexBufferLayout.h"
#include "Renderer/VertexArray.h"


class Application {
public:
    Application();

    ~Application();

    void on_event(Event& event);

    void push_layer(Layer* layer);

    void push_overlay(Layer* layer);

    void run();

    inline Window& get_window() const { return *m_window; }

    static Application* get_instance() { return s_instance; }

    static Application* create_instance() { return new Application(); }

protected:
    static Application* s_instance;

    std::unique_ptr<Window> m_window;
    ImGuiLayer* m_imgui_layer;
    LayerStack m_layerstack;
};

Application* create_application();

#endif
