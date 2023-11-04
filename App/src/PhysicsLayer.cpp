#include "PhysicsLayer.h"

#include <random>
#include "imgui/imgui.h"
#include "Util/Coordinate.h"
#include <Core/KeyCodes.h>

PhysicsLayer::PhysicsLayer() : m_camera_controller(Application::get_window().get_aspect_ratio(), 10.0f),
                               m_physics_world(AUTM_BIND(PhysicsLayer::constrain), 10) {

    std::vector<std::shared_ptr<Vertex>> vertices = {
            Vertex::create(glm::vec3(-1.0f, 1.0f, 0.0f), 0.1f, true),
            Vertex::create(glm::vec3(-1.0f, -1.0f, 0.0f), 0.1f),
            Vertex::create(glm::vec3(1.0f, -1.0f, 0.0f), 0.1f),
            Vertex::create(glm::vec3(1.0f, 1.0f, 0.0f), 0.1f),
    };

    std::vector<Edge> edges = {
            Edge(vertices[0], vertices[1]),
            Edge(vertices[1], vertices[2]),
            Edge(vertices[2], vertices[3]),
            Edge(vertices[3], vertices[0]),
            Edge(vertices[3], vertices[1])
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

    for (auto &body: m_physics_world.physics_bodies()) {
        for (auto &vertex: body.vertices()) {
            Renderer2D::draw_circle_with_radius(vertex->get_position(), vertex->get_radius());
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
    dispatcher.dispatch_event<MouseButtonPressedEvent>(AUTM_BIND(PhysicsLayer::on_mouse_clicked));
    dispatcher.dispatch_event<MouseButtonReleasedEvent>(AUTM_BIND(PhysicsLayer::on_mouse_released));
    dispatcher.dispatch_event<MouseMovedEvent>(AUTM_BIND(PhysicsLayer::on_mouse_moved));
}

EventResult PhysicsLayer::on_mouse_clicked(MouseButtonPressedEvent &event) {
    if (event.get_mouse_button() == L_MOUSE_BUTTON)
        m_mouse_down = true;
    auto point = event.get_mouse_pos();

    auto position = Coordinate::map_screen_coords_to_world_coords(
            glm::vec3(point.x, point.y, 0.0f),
            m_camera_controller.get_camera().get_projection_matrix());

//    TODO: This is temporary
    for (auto &body: m_physics_world.physics_bodies()) {
        (&body)->add_vertex(Vertex::create(glm::vec3(position.x, position.y, 0.0f), 0.1f));
    }

    return EventResult::Consume;
}

EventResult PhysicsLayer::on_mouse_released(MouseButtonReleasedEvent &event) {
    if (event.get_mouse_button() == L_MOUSE_BUTTON)
        m_mouse_down = false;
    return EventResult::Consume;
}

EventResult PhysicsLayer::on_mouse_moved(MouseMovedEvent &event) {
    if (m_mouse_down) {
        auto position = Coordinate::map_screen_coords_to_world_coords(
                glm::vec3(event.get_mouse_x(), event.get_mouse_y(), 0.0f),
                m_camera_controller.get_camera().get_projection_matrix());

        for (auto &body: m_physics_world.physics_bodies()) {
            (&body)->add_vertex(Vertex::create(glm::vec3(position.x, position.y, 0.0f), 0.1f));
        }
    }

    return EventResult::Consume;
}


void PhysicsLayer::constrain(Vertex &vertex) {
    auto position = vertex.get_position();
    auto radius = vertex.get_radius();

    if (position.y <= m_camera_controller.bottom() + radius) {
        vertex.set_position({position.x, m_camera_controller.bottom() + radius, 0.0f});
    }

    if (position.y >= m_camera_controller.top() - radius) {
        vertex.set_position({position.x, m_camera_controller.bottom() - radius, 0.0f});
    }

    if (position.x <= m_camera_controller.left() + radius) {
        vertex.set_position({position.x, m_camera_controller.bottom() + radius, 0.0f});
    }

    if (position.x >= m_camera_controller.right() - radius) {
        vertex.set_position({position.x, m_camera_controller.bottom() - radius, 0.0f});
    }
}

