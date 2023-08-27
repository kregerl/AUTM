#ifndef AUTM_LAYERSTACK_H
#define AUTM_LAYERSTACK_H

#include "autmpch.h"
#include "Layer.h"

class LayerStack {
public:
    LayerStack();

    ~LayerStack();

    void push_layer(Layer* layer);

    void pop_layer(Layer* layer);

    // Overlays are put at the back since they'll be updated first.
    void push_overlay(Layer* layer);

    void pop_overlay(Layer* layer);

    std::vector<Layer*>::iterator begin();

    std::vector<Layer*>::iterator end();

private:
    std::vector<Layer*> m_layers;
    uint32_t m_layer_index = 0;
};


#endif //AUTM_LAYERSTACK_H
