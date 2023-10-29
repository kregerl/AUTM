#include "Edge.h"

static float calculate_length(Vertex v1, Vertex v2) {
    return glm::distance(v1.get_position(), v2.get_position());
}

Edge::Edge(const std::shared_ptr<Vertex> &v1, const std::shared_ptr<Vertex> &v2)
        : m_v1(v1), m_v2(v2), m_stiffness(1.0f), m_length(calculate_length(*m_v1, *m_v2)) {}

void Edge::on_update(float ts) {
    auto v1_pos = m_v1->get_position();
    auto v2_pos = m_v2->get_position();

    auto dx = v1_pos.x - v2_pos.x;
    auto dy = v1_pos.y - v2_pos.y;

    auto distance = std::sqrt(dx * dx + dy * dy);
    auto difference = (m_length - distance) / distance * m_stiffness;

    auto x_offset = dx * difference * 0.5f;
    auto y_offset = dy * difference * 0.5f;

    auto m1 = m_v1->get_mass() + m_v2->get_mass();
    auto m2 = m_v1->get_mass() / m1;
    m1 = m_v2->get_mass() / m1;

    v1_pos.x += x_offset * m1;
    v1_pos.y += y_offset * m1;
    m_v1->set_position(v1_pos);

    v2_pos.x -= x_offset * m2;
    v2_pos.y -= y_offset * m2;
    m_v2->set_position(v2_pos);
}



