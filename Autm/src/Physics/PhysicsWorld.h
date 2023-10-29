#ifndef AUTM_PHYSICSWORLD_H
#define AUTM_PHYSICSWORLD_H

#include <autmpch.h>
#include "Vertex.h"
#include "Edge.h"
#include "PhysicsBody.h"

struct Constraint {
    glm::vec3 position;
    float radius;
};

class PhysicsWorld {
public:
    PhysicsWorld(std::function<void(Vertex&)> constraint_function, uint32_t substeps = 1);
    ~PhysicsWorld() = default;

    std::vector<PhysicsBody>& physics_bodies()  { return m_physics_bodies; }

    void add_physics_body(const PhysicsBody& body);

    void on_update(float ts);


private:
    std::vector<PhysicsBody> m_physics_bodies;
//    std::vector<PhysicsBody> m_physics_bodies;
    float m_gravity = -9.8f;
    uint32_t m_substeps;

public:
    std::function<void(Vertex&)> m_constraint;
};


#endif //AUTM_PHYSICSWORLD_H
