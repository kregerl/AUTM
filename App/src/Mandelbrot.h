#ifndef AUTM_MANDELBROT_H
#define AUTM_MANDELBROT_H

#include <Core/Layer.h>
#include <Event/MouseEvents.h>
#include <Renderer/OrthographicCamera.h>

class Mandelbrot : public Layer {

public:
    Mandelbrot();

    virtual ~Mandelbrot() = default;

    virtual void onInit() override;

    virtual void onShutdown() override;

    virtual void onUpdate(float ts) override;

    virtual void onEvent(Event& event) override;

    EventResult onMouseButtonPressed(MouseButtonPressedEvent &event);
private:
    OrthographicCamera m_camera;
    glm::vec3 m_center;


};


#endif //AUTM_MANDELBROT_H
