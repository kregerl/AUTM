#ifndef AUTM_ORTHOGRAPHICCAMERA_H
#define AUTM_ORTHOGRAPHICCAMERA_H

#include <glm/glm.hpp>


/**
 * 2D orthographic camera implementation that creates the projection and view matrices
 */
class OrthographicCamera {
public:
    OrthographicCamera() = default;

    explicit OrthographicCamera(float aspect_ratio = 1.0f, float zoom = 1.0f);

    OrthographicCamera(float left, float right, float bottom, float top, float aspect_ratio = 1.0f);

    ~OrthographicCamera() = default;

    void set_projection_matrix(float left, float right, float bottom, float top);

    void set_position(const glm::vec3& position);

    void set_rotation(float rotation);

    const glm::vec3& get_position() const { return m_position; }

    const float get_rotation() const { return m_rotation; }

    const glm::mat4& get_view_matrix() const { return m_view_matrix; }

    const glm::mat4& get_projection_matrix() const { return m_projection_matrix; }

    const glm::mat4 get_view_projection_matrix() const { return m_view_projection_matrix; }

private:
    void update_view_matrix();

private:
    glm::mat4 m_view_matrix;
    glm::mat4 m_projection_matrix;
    glm::mat4 m_view_projection_matrix;

    glm::vec3 m_position = glm::vec3(0.0f);
    float m_rotation = 0.0f;
};


#endif
