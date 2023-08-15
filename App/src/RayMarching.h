#ifndef AUTM_RAYMARCHING_H
#define AUTM_RAYMARCHING_H

#include <Core/Layer.h>
#include <Renderer/OrthographicCamera.h>
#include <Renderer/Shader.h>
#include <Renderer/VertexArray.h>

class RayMarching : public Layer {
public:
    RayMarching();

    ~RayMarching() = default;

    virtual void on_init() override;

    virtual void on_shutdown() override;

    virtual void on_update(float ts) override;

    virtual void on_event(Event& event) override;

private:
    OrthographicCamera m_camera;

    std::shared_ptr<Shader> m_shader;
    std::shared_ptr<VertexArray> m_fsQuadVA; // fullscreen quad
};


#endif //AUTM_RAYMARCHING_H
