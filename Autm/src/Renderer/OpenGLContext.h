#ifndef AUTM_OPENGLCONTEXT_H
#define AUTM_OPENGLCONTEXT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class OpenGLContext {
public:
    explicit OpenGLContext(GLFWwindow* window_handle);

    ~OpenGLContext() = default;

    void init();

    void swap_buffers();

private:
    GLFWwindow* m_window_handle;
};


#endif //AUTM_OPENGLCONTEXT_H
