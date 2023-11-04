#include "Vertex.h"

Vertex::Vertex(glm::vec3 point, float radius, float mass, bool pinned)
        : m_position(point), m_previous_position(point), m_radius(radius), m_mass(mass), m_acceleration(0), m_force(0) {}

void Vertex::on_update(float ts) {
    auto velocity = m_position - m_previous_position;
    m_previous_position = m_position;

    auto acceleration = m_acceleration;
    acceleration += m_force / m_mass;

    m_position += (velocity + acceleration) * ts;

    clear_forces();
}

void Vertex::constrain(Vertex::ConstrainFunction constrain_function) {
    constrain_function(*this);
}

void Vertex::clear_forces() {
    m_acceleration = glm::vec3(0.0f);
    m_force = glm::vec3(0.0f);
}


