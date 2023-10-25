#include "PhysicsLayer.h"
#include "autmpch.h"
#include "imgui/imgui.h"

PhysicsLayer::PhysicsLayer() : m_camera_controller(Application::get_window().get_aspect_ratio(), 10.0f),
                               m_physics_world(Constraint{.position = glm::vec3(0.0f), .radius = 5.0f}, 6) {
    std::vector<std::shared_ptr<Vertex>> vertices = {
            Vertex::create(glm::vec3(-1.5f, 1.5f, 0.0f), 0.5f),
            Vertex::create(glm::vec3(-1.5f, -1.5f, 0.0f), 0.5f),
            Vertex::create(glm::vec3(1.5f, -1.5f, 0.0f), 0.5f),
            Vertex::create(glm::vec3(1.5f, 1.5f, 0.0f), 0.5f),
    };

    std::vector<Edge> edges = {
//            Edge(vertices[0], vertices[1]),
//            Edge(vertices[1], vertices[2]),
//            Edge(vertices[2], vertices[3]),
//            Edge(vertices[3], vertices[0]),
//            Edge(vertices[3], vertices[1])
    };
    m_physics_world.add_physics_body(PhysicsBody(vertices, edges));
}

void PhysicsLayer::on_init() {
    Layer::on_init();
}

void PhysicsLayer::on_shutdown() {
    Layer::on_shutdown();
}

void PhysicsLayer::on_update(float ts) {
    Renderer2D::begin(m_camera_controller.get_camera());
    RenderSystem::clear_color(glm::vec3(0.2f));
    if (!m_paused)
        m_physics_world.on_update(ts);

    Renderer2D::draw_circle_with_radius(m_physics_world.m_constraint.position, m_physics_world.m_constraint.radius,
                                        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    for (auto &body: m_physics_world.physics_bodies()) {
        for (auto &vertex: body.vertices()) {
            Renderer2D::draw_circle(vertex->get_position(), glm::vec2(vertex->get_radius()));
        }

        for (auto &edge: body.edges()) {
            Renderer2D::draw_line(edge.get_v1()->get_position(), edge.get_v2()->get_position(), glm::vec4(1.0f));
        }
    }

    Renderer2D::end();
}

void PhysicsLayer::on_imgui_render() {
    ImGui::Begin("Settings");

    if (ImGui::Button("Play/Pause", ImVec2(24, 24))) {
        m_paused = !m_paused;
    }

    ImGui::End();
}

void PhysicsLayer::on_event(Event &event) {
    m_camera_controller.on_event(event);
    auto dispatcher = EventDispatcher(event);
    dispatcher.dispatch_event<MouseButtonPressedEvent>(AUTM_BIND_EVENT(PhysicsLayer::on_mouse_clicked));
}

EventResult PhysicsLayer::on_mouse_clicked(MouseButtonPressedEvent &event) {
    auto matrix = m_camera_controller.get_camera().get_view_projection_matrix();
    auto inverse = glm::inverse(matrix);

    AUTM_DEBUG("Transformed pos: {},{}", event.getMouseX() / (m_camera_controller.get_camera_size().x / 2.0f) - 1.0f,
               -1.0f * event.getMouseY() / (m_camera_controller.get_camera_size().y / 2.0f) - 1.0f);


    AUTM_DEBUG("Event pos: {},{}", event.getMouseX(), event.getMouseY());
    return EventResult::Consume;
}

