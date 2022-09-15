#ifndef AUTM_INPUT_H
#define AUTM_INPUT_H

#define KEYS 349

#include "autmpch.h"

#include "Event/KeyEvents.h"
#include "Event/MouseEvents.h"
#include "Event/WindowEvents.h"

class Input {
public:
    static bool isKeyPressed(int keyCode);

    static bool isMouseButtonPressed(int mouseCode);

    static glm::vec2 getMousePos();
};


#endif
