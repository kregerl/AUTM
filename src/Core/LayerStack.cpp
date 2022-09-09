#include "LayerStack.h"

LayerStack::LayerStack() {
    m_layerInsert = begin();
}

LayerStack::~LayerStack() {
    for (Layer* layer : m_layers) {
        delete layer;
    }
}

void LayerStack::pushLayer(Layer* layer) {
    m_layerInsert = m_layers.emplace(m_layerInsert, layer);
}

void LayerStack::popLayer(Layer* layer) {
    auto it = std::find(begin(), end(), layer);
    if (it != end()) {
        m_layers.erase(it);
        m_layerInsert--;
    }
}

void LayerStack::pushOverlay(Layer* layer) {
    m_layers.emplace_back(layer);
}

void LayerStack::popOverlay(Layer* layer) {
    auto it = std::find(begin(), end(), layer);
    if (it != end()) {
        m_layers.erase(it);
    }
}

std::vector<Layer*>::iterator LayerStack::begin() {
    return m_layers.begin();
}

std::vector<Layer*>::iterator LayerStack::end() {
    return m_layers.end();
}
