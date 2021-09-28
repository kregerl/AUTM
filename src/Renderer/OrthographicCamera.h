#ifndef AUTM_ORTHOGRAPHICCAMERA_H
#define AUTM_ORTHOGRAPHICCAMERA_H

#include <glm.hpp>


/**
 * 2D orthographic camera implementation that creates the projection and view matrices
 */
class OrthographicCamera {
public:
    OrthographicCamera() = default;

    OrthographicCamera(float left, float right, float bottom, float top);

    ~OrthographicCamera() = default;

    void setProjectionMatrix(float left, float right, float bottom, float top);

    void setPosition(const glm::vec3 &position);

    void setRotation(const float rotation);

    const glm::vec3 &getPosition() const { return m_position; }

    const float getRotation() const { return m_rotation; }

    const glm::mat4 &getViewMatrix() const { return m_viewMatrix; }

    const glm::mat4 &getProjectionMatrix() const { return m_projectionMatrix; }

    const glm::mat4 getViewProjectionMatrix() const { return m_viewProjectionMatrix; }

private:
    void updateViewMatrix();

private:
    glm::mat4 m_viewMatrix;
    glm::mat4 m_projectionMatrix;
    glm::mat4 m_viewProjectionMatrix;

    glm::vec3 m_position = glm::vec3(0.0f);
    float m_rotation = 0.0f;
};


#endif
