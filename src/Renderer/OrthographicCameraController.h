#ifndef AUTM_ORTHOGRAPHICCAMERACONTROLLER_H
#define AUTM_ORTHOGRAPHICCAMERACONTROLLER_H

#include <glm/glm.hpp>

#include "OrthographicCamera.h"
#include "Core/Event/MouseEvents.h"

/**
 * Controller class for the orthographic camera that allows it to move, rotate and zoom
 */
class OrthographicCameraController {
public:
    explicit OrthographicCameraController(float aspectRatio);

    ~OrthographicCameraController() = default;

    void onUpdate(double deltaTime);

    void onEvent(Event &event);

    void onMouseScrolledEvent(MouseScrolledEvent &event);

    const OrthographicCamera getCamera() const { return m_camera; }

    const glm::vec3 &getPosition() const { return m_position; }

    float getZoom() const { return m_zoom; }

    void setZoom(float zoom) { m_zoom = zoom; }

private:
    float m_zoom = 1.0f;
    float m_cameraTranslationSpeed = 2.5f;
    const float m_cameraRotationSpeed = 90.0f;
    const float m_cameraSpeed = 2.5f;
    glm::vec3 m_position = {0, 0, 0};

    OrthographicCamera m_camera;
    float m_rotation;
    float m_aspectRatio;
};


#endif
