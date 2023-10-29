#ifndef AUTM_EDGE_H
#define AUTM_EDGE_H

#include "Vertex.h"
#include "autmpch.h"

class Edge {
public:
    Edge(const std::shared_ptr<Vertex> &v1, const std::shared_ptr<Vertex> &v2);
    ~Edge() = default;

    void on_update(float ts);

    [[nodiscard]] const std::shared_ptr<Vertex> &get_v1() const { return m_v1; }

    [[nodiscard]] const std::shared_ptr<Vertex> &get_v2() const { return m_v2; }

private:
    std::shared_ptr<Vertex> m_v1;
    std::shared_ptr<Vertex> m_v2;

    float m_stiffness;
    float m_length;
};


#endif //AUTM_EDGE_H
