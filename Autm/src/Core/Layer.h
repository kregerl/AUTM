#ifndef AUTM_LAYER_H
#define AUTM_LAYER_H

#include "autmpch.h"
#include <Event/Event.h>

class Layer {
public:
    explicit Layer(const std::string& title = "Layer");

    virtual ~Layer();

    virtual void on_init() {}

    virtual void on_shutdown() {}

    virtual void on_update(float ts) {}

    virtual void on_event(Event& event) {}

    inline const std::string& get_title() const { return m_title; }

protected:
    std::string m_title;
};


#endif //AUTM_LAYER_H
