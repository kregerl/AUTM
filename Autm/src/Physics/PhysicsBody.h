#ifndef AUTM_PHYSICSBODY_H
#define AUTM_PHYSICSBODY_H

#include <autmpch.h>
#include <Core/Log.h>
#include "Vertex.h"
#include "Edge.h"

class PhysicsBody {
public:
    PhysicsBody(std::vector<Vertex> vertices, std::vector<Edge> edges);
    ~PhysicsBody() = default;

    void on_update(std::function<void(Vertex &)> constraint_function, float ts);
    void resolve_collisions();

    // TODO: Remove this
    void add_vertex(const Vertex &vertex) {
        AUTM_DEBUG("Before add_vertex: {}", m_vertices.size());
        m_vertices.emplace_back(vertex);
        AUTM_DEBUG("After add_vertex: {}", m_vertices.size());
    }

    [[nodiscard]] const std::vector<Vertex> &vertices() const { return m_vertices; }

    [[nodiscard]] const std::vector<Edge> &edges() const { return m_edges; }

private:
    std::vector<Vertex> m_vertices;
    std::vector<Edge> m_edges;
};


#endif //AUTM_PHYSICSBODY_H
