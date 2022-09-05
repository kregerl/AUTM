#include "OrthographicCamera.h"

#include <gtc/matrix_transform.hpp>
#include <Core/Log.h>

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top) : m_projectionMatrix(
        glm::ortho(left, right, bottom, top, -1.0f, 1.0f)) {
    // TODO: Debug starting points of ortho
    AUTM_CORE_DEBUG("Left: {} Right: {} Bottom: {} Top: {}", left, right, top, bottom);
    AUTM_CORE_DEBUG("Hello WOrld!");
    m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
}

void OrthographicCamera::setProjectionMatrix(float left, float right, float bottom, float top) {
    m_projectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
    m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
}

void OrthographicCamera::setPosition(const glm::vec3& position) {
    m_position = position;
    updateViewMatrix();
}

void OrthographicCamera::setRotation(const float rotation) {
    m_rotation = rotation;
    updateViewMatrix();
}

void OrthographicCamera::updateViewMatrix() {
    glm::mat4 cameraTransform = glm::translate(glm::mat4(1.0f), m_position) *
                                glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    m_viewMatrix = glm::inverse(cameraTransform);
    m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
}


