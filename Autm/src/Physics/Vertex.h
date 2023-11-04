#ifndef AUTM_VERTEX_H
#define AUTM_VERTEX_H

#include <autmpch.h>
#include <glm/glm.hpp>

class Vertex {
public:
    using ConstrainFunction = std::function<void(Vertex &)>;

    template<typename... Args>
    static std::shared_ptr<Vertex> create(Args &&... args) {
        return std::make_shared<Vertex>(std::forward<Args>(args)...);
    }

    Vertex(glm::vec3 point, float radius, float mass = 1.0f, bool pinned = false);
    ~Vertex() = default;

    void on_update(float ts);
    void constrain(ConstrainFunction constrain_function);

    [[nodiscard]] const glm::vec3 &get_position() const { return m_position; }

    void set_position(glm::vec3 position) { m_position = position; }

    [[nodiscard]] float get_mass() const { return m_mass; }

    [[nodiscard]] float get_radius() const { return m_radius; }

    void accelerate(glm::vec3 acceleration) { m_acceleration += acceleration; }

    void apply_force(glm::vec3 force) { m_force += force; }

private:
    void clear_forces();

private:
    glm::vec3 m_position;
    glm::vec3 m_previous_position;

    glm::vec3 m_acceleration;
    glm::vec3 m_force;

    float m_radius;
    float m_mass;

//    float m_friction = 0.97;
//    float m_ground_friction = 0.7;
};


#endif //AUTM_VERTEX_H
