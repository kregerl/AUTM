#ifndef AUTM_ORTHOGRAPHICCAMERACONTROLLER_H
#define AUTM_ORTHOGRAPHICCAMERACONTROLLER_H

#include <glm/glm.hpp>

#include "OrthographicCamera.h"
#include "Event/MouseEvents.h"
#include "Event/WindowEvents.h"

/**
 * Controller class for the orthographic camera that allows it to move, rotate and zoom
 */
class OrthographicCameraController {
public:
    explicit OrthographicCameraController(float aspectRatio);

    ~OrthographicCameraController() = default;

    void onUpdate(double deltaTime);

    void onEvent(Event& event);

    EventResult onMouseScrolled(MouseScrolledEvent& event);

    EventResult onWindowResized(WindowResizedEvent &event);

    const OrthographicCamera getCamera() const { return m_camera; }

    const glm::vec3& getPosition() const { return m_position; }

    float getZoom() const { return m_zoom; }

    // The camera size in coordinate space
    glm::vec2 getCameraSize() const { return {-m_aspectRatio * m_zoom, m_aspectRatio * m_zoom}; }

    void setZoom(float zoom) { m_zoom = zoom; }

    inline void disableInputs() { m_enableInputs = false; }

    inline void enableInputs() { m_enableInputs = true; }

private:
    float m_zoom = 1.0f;
    float m_cameraTranslationSpeed = 2.5f;
    const float m_cameraRotationSpeed = 90.0f;
    const float m_cameraSpeed = 2.5f;
    glm::vec3 m_position = {0, 0, 0};

    OrthographicCamera m_camera;
    float m_rotation = 0.0f;
    float m_aspectRatio;
    bool m_enableInputs = true;
};


#endif
