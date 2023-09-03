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
    explicit OrthographicCameraController(float aspect_ratio, float zoom = 1.0f);

    ~OrthographicCameraController() = default;

    void on_update(double delta_time);

    void on_event(Event& event);

    EventResult on_mouse_scrolled(MouseScrolledEvent& event);

    EventResult on_window_resized(WindowResizedEvent& event);

    const OrthographicCamera& get_camera() const { return m_camera; }

    const glm::vec3& get_position() const { return m_position; }

    float get_zoom() const { return m_zoom; }

    // The camera size in coordinate space
    glm::vec2 get_camera_size() const { return glm::vec2(m_aspect_ratio * m_zoom, m_zoom) * 2.0f; }

    void set_zoom(float zoom) { m_zoom = zoom; }

    inline void disable_inputs() { m_enable_inputs = false; }

    inline void enable_inputs() { m_enable_inputs = true; }

private:
    float m_zoom = 1.0f;
    float m_camera_translation_speed = 2.5f;
    const float m_camera_rotation_speed = 90.0f;
    const float m_camera_speed = 2.5f;
    glm::vec3 m_position = {0, 0, 0};

    OrthographicCamera m_camera;
    float m_rotation = 0.0f;
    float m_aspect_ratio;
    bool m_enable_inputs = true;
};


#endif
