#ifndef AUTM_INPUT_H
#define AUTM_INPUT_H

#define KEYS 349

#include "autmpch.h"

#include "Event/KeyEvents.h"
#include "Event/MouseEvents.h"
#include "Event/WindowEvents.h"

class Input {
public:
    static void onKeyPressedEvent(KeyPressedEvent& event);

    static void onKeyReleasedEvent(KeyReleasedEvent& event);

    static void onMouseScrolledEvent(MouseScrolledEvent& event);

    static void onMouseButtonPressedEvent(MouseButtonPressedEvent &event);

    static bool isKeyPressed(int keyCode);

    static float getScroll() { return scroll; }

    static glm::vec2 getMousePos() { return mousePos; }

private:
    static std::array<bool, KEYS> s_pressed;
    static float scroll;
    static glm::vec2 mousePos;
};


#endif
