#include "Window.h"
#include "Log.h"

Window::Window(const WindowProperties& properties) : m_windowData(properties) {


    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    m_window = glfwCreateWindow(m_windowData.width, m_windowData.height, m_windowData.title.c_str(),
                                m_windowData.isFullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);

    if (m_window == nullptr) {
        AUTM_CORE_FATAL("Cannot open a null window.");
        glfwTerminate();
    }

    m_context = new OpenGLContext(m_window);
    m_context->init();

    glfwSetWindowUserPointer(m_window, &m_windowData);

    glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    });

    glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
        WindowData& windowData = *(WindowData*) glfwGetWindowUserPointer(window);
        windowData.width = width;
        windowData.height = height;

        WindowResizedEvent event(width, height);
        windowData.callback(event);
    });


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

    glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {
        WindowData& windowData = *(WindowData*) glfwGetWindowUserPointer(window);
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);
        switch (action) {
            case GLFW_PRESS: {
                MouseButtonPressedEvent event(button, mods, xPos, yPos);
                windowData.callback(event);
                break;
            }
            case GLFW_RELEASE: {
                MouseButtonReleasedEvent event(button, mods, xPos, yPos);
                windowData.callback(event);
                break;
            }
            default:break;
        }
    });

    glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xoffset, double yoffset) {
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);
        WindowData& windowData = *(WindowData*) glfwGetWindowUserPointer(window);
        MouseScrolledEvent event(xoffset, yoffset, xPos, yPos);
        windowData.callback(event);
    });


#ifdef DEBUG
    AUTM_CORE_DEBUG("Width: {}, Height:{}", m_windowData.width, m_windowData.height);
    AUTM_CORE_DEBUG("OpenGL Version: {}", glGetString(GL_VERSION));
#endif
}


void Window::onUpdate() {
    double currentFrame = glfwGetTime();
    m_deltaTime = currentFrame - m_prevFrame;
    m_prevFrame = currentFrame;

    processInput();
}

void Window::close() {
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void Window::processInput() {
    if (Input::isKeyPressed(GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(m_window, true);
}

void Window::pollEvents() {
    m_context->swapBuffers();
    glfwPollEvents();
}

void Window::setEventCallback(eventCallbackFunction callback) {
    m_windowData.callback = callback;
}


