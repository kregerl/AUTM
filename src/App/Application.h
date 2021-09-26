#ifndef AUTM_APPLICATION_H
#define AUTM_APPLICATION_H

#include <Renderer/OrthographicCameraController.h>
#include "autmpch.h"

#include "Core/Window.h"
#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/VertexBufferLayout.h"
#include "Renderer/VertexArray.h"
#include "Renderer/OrthographicCamera.h"
#include "Core/Event/MouseEvents.h"
#include "Core/Event/KeyEvents.h"

class Application {
public:
    Application();

    void onEvent(Event &event);

    void run();

    const std::unique_ptr<Window> &getWindow() const { return m_window; }

    static Application *getInstance() { return s_instance; }

    static Application *createInstance() { return new Application(); }

private:
    static Application *s_instance;

    std::unique_ptr<Window> m_window;
    std::unique_ptr<Shader> m_shader;
    std::unique_ptr<OrthographicCameraController> m_cameraController;

    std::shared_ptr<VertexArray> m_quadVA;
    std::shared_ptr<VertexArray> m_lineVA;
};


#endif
