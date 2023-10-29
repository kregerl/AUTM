#include "PhysicsWorld.h"

PhysicsWorld::PhysicsWorld(std::function<void(Vertex &)> constraint_function, uint32_t substeps) : m_constraint(
        std::move(constraint_function)), m_substeps(substeps) {}

void PhysicsWorld::on_update(float ts) {
    for (int i = 0; i < m_substeps; i++) {
        for (auto &physics_body: m_physics_bodies) {
            physics_body.on_update(m_constraint, ts / static_cast<float>(m_substeps));
        }
    }
}

void PhysicsWorld::add_physics_body(const PhysicsBody &body) {
    m_physics_bodies.emplace_back(body);
}
