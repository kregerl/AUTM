#ifndef AUTM_PHYSICSBODY_H
#define AUTM_PHYSICSBODY_H

#include <autmpch.h>
#include "Vertex.h"
#include "Edge.h"

class PhysicsBody {
public:
    PhysicsBody(std::vector<std::shared_ptr<Vertex>> vertices, std::vector<Edge> edges);
    ~PhysicsBody() = default;

    void on_update(glm::vec3 constraint_pos, float radius, float ts);
    void resolve_collisions();

    [[nodiscard]] const std::vector<std::shared_ptr<Vertex>> &vertices() const { return m_vertices; }

    [[nodiscard]] const std::vector<Edge>& edges() const { return m_edges; }

private:
    std::vector<std::shared_ptr<Vertex>> m_vertices;
    std::vector<Edge> m_edges;
};


#endif //AUTM_PHYSICSBODY_H
