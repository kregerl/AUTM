#ifndef AUTM_LAYERSTACK_H
#define AUTM_LAYERSTACK_H

#include "autmpch.h"
#include "Layer.h"

class LayerStack {
public:
    LayerStack();

    ~LayerStack();

    void pushLayer(Layer* layer);

    void popLayer(Layer* layer);

    // Overlays are put at the back since they'll be updated first.
    void pushOverlay(Layer* layer);

    void popOverlay(Layer* layer);

    std::vector<Layer*>::iterator begin();

    std::vector<Layer*>::iterator end();

private:
    std::vector<Layer*> m_layers;
    std::vector<Layer*>::iterator m_layerInsert;
};


#endif //AUTM_LAYERSTACK_H
