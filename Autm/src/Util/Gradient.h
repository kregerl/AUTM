#ifndef AUTM_GRADIENT_H
#define AUTM_GRADIENT_H

#include "autmpch.h"
#include <glm/glm.hpp>

// Slightly modified implementation of https://gist.github.com/NickBeeuwsaert/6258245

class GradientStop {
public:
    GradientStop(float _t, glm::vec4 _val) : t(_t), value(_val) {}

private:
    float t;
    glm::vec4 value;

    friend class Gradient;
};

static inline glm::vec4 lerp(glm::vec4 s, glm::vec4 e, float t) {
    return s + (e - s) * t;
}

class Gradient {
public:
    ~Gradient();

    void add_color_stop(float t, glm::vec4 val);

    glm::vec4 get_color_at(float t);

private:
    std::vector<GradientStop*> stops;
};


#endif //AUTM_GRADIENT_H
