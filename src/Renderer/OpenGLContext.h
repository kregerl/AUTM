#ifndef AUTM_OPENGLCONTEXT_H
#define AUTM_OPENGLCONTEXT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class OpenGLContext {
public:
    OpenGLContext(GLFWwindow* windowHandle);

    void init();

    void swapBuffers();

private:
    GLFWwindow* m_windowHandle;
};


#endif //AUTM_OPENGLCONTEXT_H
