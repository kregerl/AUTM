#include "Input.h"
#include "Log.h"
#include "App/Application.h"


bool Input::is_key_pressed(int keycode) {
    auto* window = Application::get_instance()->get_window().get_opengl_window();
    return glfwGetKey(window, static_cast<uint32_t>(keycode)) == GLFW_PRESS;
}

bool Input::is_mouse_button_pressed(int mouse_code) {
    auto* window = Application::get_instance()->get_window().get_opengl_window();
    return glfwGetMouseButton(window, static_cast<uint32_t>(mouse_code)) == GLFW_PRESS;
}

glm::vec2 Input::get_mouse_position() {
    auto* window = Application::get_instance()->get_window().get_opengl_window();
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    return {x, y};
}
