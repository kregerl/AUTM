#include "Vertex.h"

Vertex::Vertex(glm::vec3 point, float radius, float mass)
        : m_position(point), m_previous_position(point), m_radius(radius), m_mass(mass), m_acceleration(0), m_force(0) {}

void Vertex::on_update(float ts) {
    auto velocity = m_position - m_previous_position;
    m_previous_position = m_position;

    auto acceleration = m_acceleration;
    acceleration += m_force / m_mass;

    m_position += (velocity + acceleration) * ts;

    clear_forces();
}

void Vertex::constrain(glm::vec3 position, float radius) {
    const glm::vec3 distance_to_object = position - m_position;
    const float dist = std::sqrt(
            distance_to_object.x * distance_to_object.x + distance_to_object.y * distance_to_object.y);
    if (dist > (radius - (m_radius / 2.0f))) {
        const glm::vec3 n = distance_to_object / dist;
        m_position = position - n * (radius - (m_radius / 2.0f));
    }
}

void Vertex::clear_forces() {
    m_acceleration = glm::vec3(0.0f);
    m_force = glm::vec3(0.0f);
}

