#include "Input.h"
#include "Log.h"
#include "App/Application.h"


bool Input::isKeyPressed(int keyCode) {
    auto* window = Application::getInstance()->getWindow().getOpenglWindow();
    return glfwGetKey(window, static_cast<uint32_t>(keyCode)) == GLFW_PRESS;
}

bool Input::isMouseButtonPressed(int mouseCode) {
    auto* window = Application::getInstance()->getWindow().getOpenglWindow();
    return glfwGetMouseButton(window, static_cast<uint32_t>(mouseCode)) == GLFW_PRESS;
}

glm::vec2 Input::getMousePos() {
    auto* window = Application::getInstance()->getWindow().getOpenglWindow();
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    return {x, y};
}
