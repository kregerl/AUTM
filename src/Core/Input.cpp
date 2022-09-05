#include "Input.h"
#include "KeyCodes.h"
#include "Log.h"

#ifdef DEBUG
// Change this number to 0 to prevent keys from being printed
#if 0
#include "Log.h"
#define DEBUG_KEYS
#endif
#endif

std::array<bool, KEYS> Input::s_pressed = {false};
// TODO: Remove this, only 0.5f for the mandelbrot set
float Input::scroll = 1.0f;
glm::vec2 Input::mousePos = {};

void Input::onKeyPressedEvent(KeyPressedEvent& event) {
    int keyCode = event.getKeyCode();
    s_pressed[keyCode] = true;
#ifdef DEBUG_KEYS
    AUTM_CORE_DEBUG("Pressed: {}", keyCode);
#endif
}

void Input::onKeyReleasedEvent(KeyReleasedEvent& event) {
    int keyCode = event.getKeyCode();
    s_pressed[keyCode] = false;
#ifdef DEBUG_KEYS
    AUTM_CORE_DEBUG("Released: {}", keyCode);
#endif
}

/**
 * Returns whether or not the specified key is currently being pressed OR being held down.
 * Works when two keys are held down at the same time.
 * @param keyCode - The keycode of the key
 * @return True if the key is being pressed or held
 */
bool Input::isKeyPressed(int keyCode) {
    if (keyCode >= KEYS) return false;
    return s_pressed[keyCode];
}

void Input::onMouseScrolledEvent(MouseScrolledEvent& event) {
    float scrollAmount = 0.01f;
    if (Input::isKeyPressed(KEY_LEFT_CONTROL)) {
        scrollAmount = 0.001f;
    }
    float amount = static_cast<float>((event.getMouseOffsetY() * scrollAmount));
    float min = std::min(scroll + amount, 2.0f);

    scroll += scroll * 0.5 * event.getMouseOffsetY();
    AUTM_CORE_DEBUG("Scroll: {}", 1 / scroll);
}

void Input::onMouseButtonPressedEvent(MouseButtonPressedEvent& event) {
    if (event.getMouseButton() == L_MOUSE_BUTTON) {
        mousePos = event.getMousePos();
    }
}


