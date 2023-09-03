#include <Core/Log.h>
#include "OrthographicCameraController.h"
#include "Core/Input.h"
#include "Core/KeyCodes.h"

OrthographicCameraController::OrthographicCameraController(float aspect_ratio, float zoom) :
        m_aspect_ratio(aspect_ratio),
        m_zoom(zoom),
        m_camera(-aspect_ratio * m_zoom, aspect_ratio * m_zoom, -m_zoom, m_zoom),
        m_rotation(0.0f) {
}

void OrthographicCameraController::on_update(double delta_time) {
    if (m_enable_inputs) {
        if (Input::is_key_pressed(KEY_W)) {
            m_position.x += -sin(glm::radians(m_rotation)) * m_camera_translation_speed * delta_time;
            m_position.y += cos(glm::radians(m_rotation)) * m_camera_translation_speed * delta_time;
        }
        if (Input::is_key_pressed(KEY_A)) {
            m_position.y -= sin(glm::radians(m_rotation)) * m_camera_translation_speed * delta_time;
            m_position.x -= cos(glm::radians(m_rotation)) * m_camera_translation_speed * delta_time;
        }
        if (Input::is_key_pressed(KEY_S)) {
            m_position.x -= -sin(glm::radians(m_rotation)) * m_camera_translation_speed * delta_time;
            m_position.y -= cos(glm::radians(m_rotation)) * m_camera_translation_speed * delta_time;
        }
        if (Input::is_key_pressed(KEY_D)) {
            m_position.x += cos(glm::radians(m_rotation)) * m_camera_translation_speed * delta_time;
            m_position.y += sin(glm::radians(m_rotation)) * m_camera_translation_speed * delta_time;
        }
    }

    m_camera.set_position(m_position);

    if (m_enable_inputs) {
        if (Input::is_key_pressed(KEY_Q)) {
            m_rotation += m_camera_rotation_speed * delta_time;
        }
        if (Input::is_key_pressed(KEY_E)) {
            m_rotation -= m_camera_rotation_speed * delta_time;
        }

        if (m_rotation > 180.0f) {
            m_rotation -= 360.0f;
        } else if (m_rotation <= -180.0f) {
            m_rotation += 360.0f;
        }
    }
    m_camera.set_rotation(m_rotation);

    m_camera_translation_speed = m_camera_speed * m_zoom;

}

void OrthographicCameraController::on_event(Event& event) {
    EventDispatcher dispatcher(event);
    dispatcher.dispatch_event<MouseScrolledEvent>(AUTM_BIND_EVENT(OrthographicCameraController::on_mouse_scrolled));
    dispatcher.dispatch_event<WindowResizedEvent>(AUTM_BIND_EVENT(OrthographicCameraController::on_window_resized));
}

EventResult OrthographicCameraController::on_mouse_scrolled(MouseScrolledEvent& event) {
    if (m_enable_inputs) {
        m_zoom -= event.getMouseOffsetY() * 0.25f;
        m_zoom = std::max(m_zoom, 0.1f);
        m_camera.set_projection_matrix(-m_aspect_ratio * m_zoom, m_aspect_ratio * m_zoom, -m_zoom, m_zoom);
    }
    return EventResult::Consume;
}

EventResult OrthographicCameraController::on_window_resized(WindowResizedEvent& event) {
    m_aspect_ratio = (float) event.get_width() / (float) event.get_height();
    m_camera.set_projection_matrix(-m_aspect_ratio * m_zoom, m_aspect_ratio * m_zoom, -m_zoom, m_zoom);
    return EventResult::Consume;
}


