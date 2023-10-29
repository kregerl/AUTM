#include <Renderer/Renderer2D.h>
#include <Renderer/RenderSystem.h>
#include <App/Application.h>
#include <Core/Log.h>
#include <Util/Primitives.h>
#include "CustomShader.h"

CustomShader::CustomShader() : m_camera_controller(Application::get_window().get_aspect_ratio(), 1.0f) {
    m_sand_texture = std::make_shared<Texture2D>("/home/loucas/CLionProjects/autm/assets/images/sand.png");

    m_shader = std::make_shared<Shader>("/home/loucas/CLionProjects/autm/assets/shaders/CustomVert.glsl",
                                        "/home/loucas/CLionProjects/autm/assets/shaders/CustomFrag.glsl");

    m_blur = std::make_shared<Shader>("/home/loucas/CLionProjects/autm/assets/shaders/core/BlurVert.glsl",
                                      "/home/loucas/CLionProjects/autm/assets/shaders/core/BlurFrag.glsl");
    auto aspect_ratio = Application::get_window().get_aspect_ratio();

    m_quad_va = Primitives::generate_fullscreen_quad(aspect_ratio);
//    float vertices[4 * 5] = {
//            -aspect_ratio, -1.0f, 0.0f, 0.0f, 0.0f,
//            aspect_ratio, -1.0f, 0.0f, 1.0f, 0.0f,
//            aspect_ratio, 1.0f, 0.0f, 1.0f, 1.0f,
//            -aspect_ratio, 1.0f, 0.0f, 0.0f, 1.0f
//    };
//    uint32_t indices[2 * 3] = {
//            0, 1, 3,
//            1, 2, 3
//    };
//    m_quad_va = std::make_shared<VertexArray>();
//    std::shared_ptr<VertexBuffer> vertexBuffer = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));
//    vertexBuffer->set_layout({
//                                     {ShaderDataType::Vec3f, "a_position"},
//                                     {ShaderDataType::Vec2f, "a_texture_coordinate"},
//                             });
//    m_quad_va->add_vertex_buffer(vertexBuffer);
//    std::shared_ptr<IndexBuffer> indexBuffer = std::make_shared<IndexBuffer>(indices,
//                                                                             sizeof(indices) / sizeof(uint32_t));
//    m_quad_va->set_index_buffer(indexBuffer);
}

void CustomShader::on_init() {
    FramebufferSpecification spec;
    spec.width = Application::get_window().get_width();
    spec.height = Application::get_window().get_height();
    spec.attachments = FramebufferAttachmentSpecification(
            {FramebufferTextureSpecification(FramebufferTextureSpecification::TextureFormat::RGBA8)});
    m_framebuffer = std::make_unique<Framebuffer>(spec);
}

void CustomShader::on_shutdown() {}

void CustomShader::on_update(float ts) {

    if (FramebufferSpecification spec = m_framebuffer->get_specification();
            m_viewport_size.x > 0.0f && m_viewport_size.y > 0.0f && // zero sized framebuffer is invalid
            (spec.width != m_viewport_size.x || spec.height != m_viewport_size.y)) {
        m_framebuffer->resize((uint32_t) m_viewport_size.x, (uint32_t) m_viewport_size.y);
    }

    m_camera_controller.on_update(ts);

    m_framebuffer->bind();
    RenderSystem::clear_color(0.2f, 0.2f, 0.2f, 1.0f);
    Renderer2D::begin(m_camera_controller.get_camera());

    Renderer2D::draw_quad(glm::vec3(0.0f), glm::vec2(1.0f), m_sand_texture, 10.0f);

    Renderer2D::end();
    m_framebuffer->unbind();

    RenderSystem::clear_color(0.2f, 0.2f, 0.2f, 1.0f);
    Renderer2D::begin(m_camera_controller.get_camera());

    m_framebuffer->bind_color_attachment_id();
    Renderer2D::submit(m_blur, m_quad_va);

    Renderer2D::end();
}

void CustomShader::on_event(Event& event) {
    EventDispatcher dispatcher(event);
    dispatcher.dispatch_event<WindowResizedEvent>(AUTM_BIND(CustomShader::on_window_resized));

    m_camera_controller.on_event(event);
}

EventResult CustomShader::on_window_resized(WindowResizedEvent& event) {
    m_viewport_size = event.get_size();
    return EventResult::Pass;
}

void CustomShader::on_imgui_render() {
    Layer::on_imgui_render();
}
