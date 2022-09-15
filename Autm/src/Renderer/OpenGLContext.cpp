#include "OpenGLContext.h"
#include <Core/Log.h>

OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_windowHandle(windowHandle) {}

void OpenGLContext::init() {
    glfwMakeContextCurrent(m_windowHandle);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        AUTM_CORE_FATAL("Failed to load GLAD.");
}

void OpenGLContext::swapBuffers() {
    glfwSwapBuffers(m_windowHandle);
}

