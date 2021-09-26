#ifndef AUTM_INPUT_H
#define AUTM_INPUT_H

#define KEYS 349

#include "autmpch.h"

#include "Event/KeyEvents.h"
#include "Event/MouseEvents.h"

class Input {
public:
    static void onKeyPressedEvent(KeyPressedEvent &event);

    static void onKeyReleasedEvent(KeyReleasedEvent &event);

    static bool isKeyPressed(int keyCode);


private:
    static std::array<bool, KEYS> s_pressed;
};


#endif
