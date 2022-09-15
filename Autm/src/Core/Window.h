#ifndef AUTM_WINDOW_H
#define AUTM_WINDOW_H

#include "autmpch.h"
#include <Renderer/OpenGLContext.h>

#include "Input.h"


struct WindowProperties {
    int width, height;
    std::string_view title;
    bool isFullscreen;

    WindowProperties(int width = 1280,
                     int height = 720,
                     std::string_view title = "Title",
                     bool isFullscreen = false)
            : width(width),
              height(height),
              title(title),
              isFullscreen(isFullscreen) {}
};


class Window {
public:
    using eventCallbackFunction = std::function<void(Event&)>;

    Window(const WindowProperties& properties);

    ~Window() = default;

    void onUpdate();

    void close();

    void pollEvents();

    void setEventCallback(eventCallbackFunction callback);

    glm::vec2 getResolution() const { return {m_windowData.width, m_windowData.height}; }

    int getWidth() const { return m_windowData.width; }

    int getHeight() const { return m_windowData.height; }

    bool shouldClose() const { return glfwWindowShouldClose(m_window); }

    double getDeltaTime() const { return m_deltaTime; }

    GLFWwindow* getOpenglWindow() const { return m_window; }


private:
    void processInput();

private:
    GLFWwindow* m_window;
    double m_deltaTime = 0.0f, m_prevFrame = 0.0f;
    OpenGLContext* m_context;
    struct WindowData {
        int width, height;
        std::string_view title;
        bool isFullscreen;
        eventCallbackFunction callback;

        explicit WindowData(const WindowProperties& properties) : width(properties.width), height(properties.height),
                                                                  title(properties.title),
                                                                  isFullscreen(properties.isFullscreen) {}
    };

    WindowData m_windowData;

};


#endif
