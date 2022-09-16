#ifndef AUTM_MANDELBROT_H
#define AUTM_MANDELBROT_H

#include <Core/Layer.h>
#include <Event/MouseEvents.h>
#include <Renderer/OrthographicCamera.h>
#include <Renderer/Shader.h>
#include <Renderer/VertexArray.h>

class Mandelbrot : public Layer {

public:
    Mandelbrot();

    virtual ~Mandelbrot() = default;

    virtual void onInit() override;

    virtual void onShutdown() override;

    virtual void onUpdate(float ts) override;

    virtual void onEvent(Event& event) override;

    EventResult onMouseButtonPressed(MouseButtonPressedEvent &event);

    EventResult onMouseScroll(MouseScrolledEvent &event);
private:
    OrthographicCamera m_camera;
    glm::vec2 m_center = glm::vec2(0.0f);
    float m_zoom = 1.0f;

    std::shared_ptr<Shader> m_fractalShader;
    std::shared_ptr<VertexArray> m_fsQuadVA; // fullscreen quad
};


#endif //AUTM_MANDELBROT_H
