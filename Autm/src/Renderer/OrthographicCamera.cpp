#include "OrthographicCamera.h"

#include <gtc/matrix_transform.hpp>
#include <Core/Log.h>

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float aspect_ratio)
        : m_projection_matrix(
        glm::ortho(left * aspect_ratio, right * aspect_ratio, bottom, top, -1.0f, 1.0f)) {
    AUTM_CORE_DEBUG("Orthographic Projection Matrix:: Left: {} Right: {} Bottom: {} Top: {}", left * aspect_ratio,
                    right * aspect_ratio, bottom, top);
    update_view_matrix();
}

void OrthographicCamera::set_projection_matrix(float left, float right, float bottom, float top) {
    m_projection_matrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
    m_view_projection_matrix = m_projection_matrix * m_view_matrix;
}

void OrthographicCamera::set_position(const glm::vec3& position) {
    m_position = position;
    update_view_matrix();
}

void OrthographicCamera::set_rotation(const float rotation) {
    m_rotation = rotation;
    update_view_matrix();
}

void OrthographicCamera::update_view_matrix() {
    glm::mat4 cameraTransform = glm::translate(glm::mat4(1.0f), m_position) *
                                glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    m_view_matrix = glm::inverse(cameraTransform);
    m_view_projection_matrix = m_projection_matrix * m_view_matrix;
}


