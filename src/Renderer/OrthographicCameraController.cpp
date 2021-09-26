#include "OrthographicCameraController.h"
#include "Core/Input.h"
#include "Core/KeyCodes.h"



OrthographicCameraController::OrthographicCameraController(float aspectRatio) :
        m_aspectRatio(aspectRatio),
        m_camera(-aspectRatio * m_zoom, aspectRatio * m_zoom, -m_zoom, m_zoom),
        m_rotation(0.0f) {
}

void OrthographicCameraController::onUpdate(double deltaTime) {



    if (Input::isKeyPressed(KEY_W)) {
        m_position.x += -sin(glm::radians(m_rotation)) * m_cameraTranslationSpeed * deltaTime;
        m_position.y += cos(glm::radians(m_rotation)) * m_cameraTranslationSpeed * deltaTime;
    }
    if (Input::isKeyPressed(KEY_A)) {
        m_position.y -= sin(glm::radians(m_rotation)) * m_cameraTranslationSpeed * deltaTime;
        m_position.x -= cos(glm::radians(m_rotation)) * m_cameraTranslationSpeed * deltaTime;
    }
    if (Input::isKeyPressed(KEY_S)) {
        m_position.x -= -sin(glm::radians(m_rotation)) * m_cameraTranslationSpeed * deltaTime;
        m_position.y -= cos(glm::radians(m_rotation)) * m_cameraTranslationSpeed * deltaTime;
    }
    if (Input::isKeyPressed(KEY_D)) {
        m_position.x += cos(glm::radians(m_rotation)) * m_cameraTranslationSpeed * deltaTime;
        m_position.y += sin(glm::radians(m_rotation)) * m_cameraTranslationSpeed * deltaTime;
    }

    m_camera.setPosition(m_position);

    if (Input::isKeyPressed(KEY_Q)) {
        m_rotation += m_cameraRotationSpeed * deltaTime;
    }
    if (Input::isKeyPressed(KEY_E)) {
        m_rotation -= m_cameraRotationSpeed * deltaTime;
    }

    if (m_rotation > 180.0f) {
        m_rotation -= 360.0f;
    } else if (m_rotation <= -180.0f) {
        m_rotation += 360.0f;
    }
    m_camera.setRotation(m_rotation);

    m_cameraTranslationSpeed = m_cameraSpeed * m_zoom;


}

void OrthographicCameraController::onEvent(Event &event) {
    EventDispatcher dispatcher(event);
    dispatcher.dispatchEvent<MouseScrolledEvent>(BIND_EVENT_FUNCTION(OrthographicCameraController::onMouseScrolledEvent));
}

void OrthographicCameraController::onMouseScrolledEvent(MouseScrolledEvent &event) {
    m_zoom -= event.getMouseOffsetY() * 0.25f;
//    For some weird effects, remove the limiter below to flip the camera after moving through the world space
    m_zoom = std::max(m_zoom, 0.25f);
    m_camera.setProjectionMatrix(-m_aspectRatio * m_zoom, m_aspectRatio * m_zoom, -m_zoom, m_zoom);

}

