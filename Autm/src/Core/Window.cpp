#include "Window.h"

#include <utility>
#include "Log.h"
#include "Renderer/RenderSystem.h"

Window::Window(const WindowProperties& properties) : m_window_data(properties) {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    m_window = glfwCreateWindow(m_window_data.width, m_window_data.height, m_window_data.title.data(),
                                m_window_data.is_fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);

    if (m_window == nullptr) {
        AUTM_CORE_FATAL("Cannot open a null window.");
        glfwTerminate();
    }

    m_context = new OpenGLContext(m_window);
    m_context->init();

    glfwSetWindowUserPointer(m_window, &m_window_data);

    // WindowResizedEvent
    glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
        WindowData& windowData = *(WindowData*) glfwGetWindowUserPointer(window);
        windowData.width = width;
        windowData.height = height;

        WindowResizedEvent event(width, height);
        windowData.callback(event);
    });

    // WindowClosedEvent
    glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
        WindowData& windowData = *(WindowData*) glfwGetWindowUserPointer(window);
        WindowClosedEvent event;
        windowData.callback(event);
    });

    // KeyPressedEvent / KeyReleasedEvent
    glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        WindowData& windowData = *(WindowData*) glfwGetWindowUserPointer(window);
        switch (action) {
            case GLFW_PRESS: {
                KeyPressedEvent event(key, mods);
                windowData.callback(event);
                break;
            }
            case GLFW_REPEAT: {
                KeyPressedEvent event(key, mods, true);
                windowData.callback(event);
                break;
            }
            case GLFW_RELEASE: {
                KeyReleasedEvent event(key, mods);
                windowData.callback(event);
                break;
            }
            default:break;
        }
    });

    // MouseButtonPressedEvent / MouseButtonReleaseEvent
    glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {
        WindowData& windowData = *(WindowData*) glfwGetWindowUserPointer(window);
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);
        switch (action) {
            case GLFW_PRESS: {
                MouseButtonPressedEvent event(button, mods, (float) xPos, (float) yPos);
                windowData.callback(event);
                break;
            }
            case GLFW_RELEASE: {
                MouseButtonReleasedEvent event(button, mods, (float) xPos, (float) yPos);
                windowData.callback(event);
                break;
            }
            default:break;
        }
    });

    // MouseScrolledEvent
    glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xoffset, double yoffset) {
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);
        WindowData& windowData = *(WindowData*) glfwGetWindowUserPointer(window);
        MouseScrolledEvent event((float) xoffset, (float) yoffset, (float) xPos, (float) yPos);
        windowData.callback(event);
    });

    // MouseMovedEvent
    glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double x, double y) {
        WindowData& windowData = *(WindowData*) glfwGetWindowUserPointer(window);
        MouseMovedEvent event((float) x, (float) y);
        windowData.callback(event);
    });


#ifdef DEBUG
    AUTM_CORE_DEBUG("Width: {}, Height:{}", m_window_data.width, m_window_data.height);
    AUTM_CORE_DEBUG("OpenGL Version: {}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
#endif
}


void Window::onUpdate() {
    double currentFrame = glfwGetTime();
    m_delta_time = currentFrame - m_previous_frame;
    m_previous_frame = currentFrame;

    process_input();
}

void Window::process_input() {
    if (Input::is_key_pressed(GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(m_window, true);
}

void Window::poll_events() {
    m_context->swap_buffers();
    glfwPollEvents();
}

void Window::set_event_callback(EventCallbackFunction callback) {
    m_window_data.callback = std::move(callback);
}

Window::~Window() {
    glfwDestroyWindow(m_window);
    glfwTerminate();
}


