#ifndef AUTM_WINDOW_H
#define AUTM_WINDOW_H

#include "autmpch.h"
#include <Renderer/OpenGLContext.h>

#include "Input.h"


struct WindowProperties {
    int width, height;
    std::string_view title;
    bool is_fullscreen;

    WindowProperties(int width = 1280,
                     int height = 720,
                     std::string_view title = "Title",
                     bool is_fullscreen = false)
            : width(width),
              height(height),
              title(title),
              is_fullscreen(is_fullscreen) {}
};


class Window {
public:
    using EventCallbackFunction = std::function<void(Event&)>;

    explicit Window(const WindowProperties& properties);

    ~Window();

    void onUpdate();

    void poll_events();

    void set_event_callback(EventCallbackFunction callback);

    glm::vec2 get_resolution() const { return {m_window_data.width, m_window_data.height}; }

    float get_aspect_ratio() const { return (float) m_window_data.width / (float) m_window_data.height; }

    int get_width() const { return m_window_data.width; }

    int get_height() const { return m_window_data.height; }

    bool should_close() const { return glfwWindowShouldClose(m_window); }

    double get_delta_time() const { return m_delta_time; }

    GLFWwindow* get_opengl_window() const { return m_window; }


private:
    void process_input();

private:
    GLFWwindow* m_window;
    double m_delta_time = 0.0f, m_previous_frame = 0.0f;
    OpenGLContext* m_context;

    struct WindowData {
        int width, height;
        std::string_view title;
        bool is_fullscreen;
        EventCallbackFunction callback;

        explicit WindowData(const WindowProperties& properties) : width(properties.width), height(properties.height),
                                                                  title(properties.title),
                                                                  is_fullscreen(properties.is_fullscreen) {}
    };

    WindowData m_window_data;

};


#endif
