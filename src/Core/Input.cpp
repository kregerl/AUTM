#include "Input.h"

#ifdef DEBUG
    // Change this number to 0 to prevent keys from being printed
    #if 0
        #define DEBUG_KEYS
    #endif
#endif

std::array<bool, KEYS> Input::s_pressed = {false};

void Input::onKeyPressedEvent(KeyPressedEvent &event) {
    int keyCode = event.getKeyCode();
    s_pressed[keyCode] = true;
#ifdef DEBUG_KEYS
    std::cout << "Pressed: " << keyCode << std::endl;
#endif
}

void Input::onKeyReleasedEvent(KeyReleasedEvent &event) {
    int keyCode = event.getKeyCode();
    s_pressed[keyCode] = false;
#ifdef DEBUG_KEYS
    std::cout << "Released: " << keyCode << std::endl;
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

