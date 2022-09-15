#ifndef AUTM_APPLICATION_H
#define AUTM_APPLICATION_H

#include "autmpch.h"
#include "Renderer/OrthographicCameraController.h"
#include "Core/LayerStack.h"
#include "Core/Window.h"
#include "Renderer/Shader.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/VertexBufferLayout.h"
#include "Renderer/VertexArray.h"
#include "Renderer/OrthographicCamera.h"
#include "Renderer/Texture2D.h"
#include "Event/MouseEvents.h"
#include "Event/KeyEvents.h"


class Application {
public:
    Application();

    ~Application();

    void onEvent(Event& event);

    void pushLayer(Layer* layer);

    void pushOverlay(Layer* layer);

    void run();

    const std::unique_ptr<Window>& getWindow() const { return m_window; }

    static Application* getInstance() { return s_instance; }

    static Application* createInstance() { return new Application(); }

protected:
    static Application* s_instance;

    std::unique_ptr<Window> m_window;
//    std::unique_ptr<OrthographicCameraController> m_cameraController;

    LayerStack m_layerStack;
//    glm::vec3 m_center;
};

Application* createApplication();

#endif
