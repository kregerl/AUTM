#include "OpenGLContext.h"
#include <Core/Log.h>

OpenGLContext::OpenGLContext(GLFWwindow* window_handle) : m_window_handle(window_handle) {}

void OpenGLContext::init() {
    glfwMakeContextCurrent(m_window_handle);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        AUTM_CORE_FATAL("Failed to load GLAD.");
}

void OpenGLContext::swap_buffers() {
    glfwSwapBuffers(m_window_handle);
}

