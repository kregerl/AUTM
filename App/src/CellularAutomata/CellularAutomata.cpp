#include <Util/Primitives.h>
#include "CellularAutomata.h"

CellularAutomata::CellularAutomata() : m_camera(Application::get_window().get_aspect_ratio()) {
    m_vertex_array = Primitives::generate_fullscreen_quad(Application::get_window().get_aspect_ratio());

    m_passthrough_shader = std::make_shared<Shader>(
            "/home/loucas/CLionProjects/Autm/assets/shaders/core/PassthroughVert.glsl",
            "/home/loucas/CLionProjects/Autm/assets/shaders/core/PassthroughFrag.glsl");
}

void CellularAutomata::on_init() {
    FramebufferSpecification spec;
    spec.width = Application::get_window().get_width();
    spec.height = Application::get_window().get_height();
    spec.attachments = FramebufferAttachmentSpecification(
            {FramebufferTextureSpecification(FramebufferTextureSpecification::TextureFormat::RGBA8)});
    m_current_framebuffer = std::make_unique<Framebuffer>(FramebufferSpecification(spec));
    m_previous_framebuffer = std::make_unique<Framebuffer>(FramebufferSpecification(spec));
}

void CellularAutomata::on_shutdown() {
    Layer::on_shutdown();
}

void CellularAutomata::on_update(float ts) {
    if (FramebufferSpecification spec = m_current_framebuffer->get_specification();
            m_viewport_size.x > 0.0f && m_viewport_size.y > 0.0f && // zero sized framebuffer is invalid
            (spec.width != m_viewport_size.x || spec.height != m_viewport_size.y)) {
        m_current_framebuffer->resize((uint32_t) m_viewport_size.x, (uint32_t) m_viewport_size.y);
        m_previous_framebuffer->resize((uint32_t) m_viewport_size.x, (uint32_t) m_viewport_size.y);
        AUTM_DEBUG("Resizing framebuffers");
    }
    m_current_frame += 1;

    if (m_simulation.should_reset()) {
        m_regenerate = true;
        m_total_displayed_frames = 0;
    }

    if (m_current_frame % m_simulation.get_update_rate() == 0 && !m_simulation.is_paused()) {
        m_total_displayed_frames += 1;
        m_current_frame = 0;
        m_current_framebuffer->bind();
        {
            RenderSystem::clear_color(0.0f, 0.0f, 0.0f);
            Renderer2D::begin(m_camera);

            m_previous_framebuffer->bind_color_attachment_id();
            auto shader = m_simulation.simulate();
            shader->bind();
            shader->set_uint("u_frame", m_total_displayed_frames);
            shader->set_bool("u_regenerate", m_regenerate);
            if (m_regenerate)
                m_regenerate = false;
            shader->set_vec2("u_resolution", Application::get_window().get_resolution());
            shader->unbind();
            Renderer2D::submit(shader, m_vertex_array);

            Renderer2D::end();
        }
        m_current_framebuffer->unbind();

        RenderSystem::clear_color(0.0f, 0.0f, 0.0f, 1.0f);
        Renderer2D::begin(m_camera);

        m_current_framebuffer->bind_color_attachment_id();
        Renderer2D::submit(m_passthrough_shader, m_vertex_array);

        Renderer2D::end();

        std::unique_ptr<Framebuffer> tmp = std::move(m_current_framebuffer);
        m_current_framebuffer = std::move(m_previous_framebuffer);
        m_previous_framebuffer = std::move(tmp);
    }
}

void CellularAutomata::on_event(Event& event) {
    EventDispatcher dispatcher(event);
    dispatcher.dispatch_event<WindowResizedEvent>(AUTM_BIND_EVENT(CellularAutomata::on_window_resized));
}

void CellularAutomata::on_imgui_render() {
    m_simulation.on_imgui_render();
}

EventResult CellularAutomata::on_window_resized(WindowResizedEvent& event) {
    m_viewport_size = event.get_size();
    return EventResult::Consume;
}