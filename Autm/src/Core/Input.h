#ifndef AUTM_INPUT_H
#define AUTM_INPUT_H

#define KEYS 349

#include "autmpch.h"

#include "Event/KeyEvents.h"
#include "Event/MouseEvents.h"
#include "Event/WindowEvents.h"

class Input {
public:
    static bool is_key_pressed(int keycode);

    static bool is_mouse_button_pressed(int mouse_code);

    static glm::vec2 get_mouse_position();
};


#endif
