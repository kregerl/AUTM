#include "Gradient.h"

Gradient::~Gradient() {
    for (auto& stop: stops) {
        delete stop;
    }
}

void Gradient::add_color_stop(float t, glm::vec4 val) {
    std::vector<GradientStop*>::iterator it;
    for (it = stops.begin(); it != stops.end(); it++) {
        if ((*it)->t > t)break;
    }

    stops.insert(it, new GradientStop(t, val));
}

glm::vec4 Gradient::get_color_at(float t) {
    std::vector<GradientStop*>::iterator it;
    GradientStop* start, * stop;
    for (it = stops.begin(); it != stops.end(); it++) {
        stop = *it;
        if (stop->t > t)
            break;
    }
    if (it == stops.begin() || it == stops.end()) return stop->value;
    start = *(--it);
    float frac = (t - start->t) / (stop->t - start->t);
    return lerp(start->value, stop->value, frac);
}