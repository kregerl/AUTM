#ifndef AUTM_LAYER_H
#define AUTM_LAYER_H

#include "autmpch.h"
#include <Core/Event/Event.h>

class Layer {
public:
    Layer(const std::string& title = "Layer");

    virtual ~Layer();

    virtual void onInit() {}

    virtual void onShutdown() {}

    virtual void onUpdate() {}

    virtual void onEvent(Event& event) {}

    inline const std::string& getTitle() const { return m_title; }

protected:
    std::string m_title;
};


#endif //AUTM_LAYER_H
