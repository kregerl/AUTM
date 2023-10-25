#include "PhysicsBody.h"

PhysicsBody::PhysicsBody(std::vector<std::shared_ptr<Vertex>> vertices, std::vector<Edge> edges)
        : m_vertices(std::move(vertices)), m_edges(std::move(edges)) {}

void PhysicsBody::on_update(glm::vec3 constraint_pos, float radius, float ts) {
    resolve_collisions();
    for (auto &vertex: m_vertices) {
        vertex->accelerate({0.0f, -9.8f, 0.0f});
        vertex->constrain(constraint_pos, radius);
        vertex->on_update(ts);
    }

    for (auto &edge: m_edges) {
        edge.on_update(ts);
    }
}

void PhysicsBody::resolve_collisions() {
    for (uint32_t i = 0; i < m_vertices.size(); i++) {
        auto &vertex1 = m_vertices.at(i);
        for (uint32_t j = i + 1; j < m_vertices.size(); j++) {
            auto &vertex2 = m_vertices.at(j);
            const glm::vec3 distance_to_object = vertex1->get_position() - vertex2->get_position();
            const float distance = std::sqrt(
                    distance_to_object.x * distance_to_object.x + distance_to_object.y * distance_to_object.y);
            if (distance < (vertex1->get_radius() + vertex2->get_radius()) / 2.0f) {
                const auto n = distance_to_object / distance;
                vertex1->set_position(
                        vertex1->get_position() - n * ((vertex1->get_radius() + vertex2->get_radius()) / 2.0f));
                vertex2->set_position(
                        vertex2->get_position() + n * ((vertex1->get_radius() + vertex2->get_radius()) / 2.0f));
            }
        }
    }
}

