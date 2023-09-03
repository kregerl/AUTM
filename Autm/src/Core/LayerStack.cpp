#include "LayerStack.h"

LayerStack::LayerStack() {}

LayerStack::~LayerStack() {
    for (Layer* layer: m_layers) {
        delete layer;
    }
}

void LayerStack::push_layer(Layer* layer) {
    m_layers.emplace(m_layers.begin() + m_layer_index, layer);
    m_layer_index++;
}

void LayerStack::pop_layer(Layer* layer) {
    auto it = std::find(begin(), begin() + m_layer_index, layer);
    if (it != begin() + m_layer_index) {
        layer->on_shutdown();
        m_layers.erase(it);
        m_layer_index--;
    }
}

void LayerStack::push_overlay(Layer* layer) {
    m_layers.emplace_back(layer);
}

void LayerStack::pop_overlay(Layer* layer) {
    auto it = std::find(begin() + m_layer_index, end(), layer);
    if (it != end()) {
        layer->on_shutdown();
        m_layers.erase(it);
    }
}

std::vector<Layer*>::iterator LayerStack::begin() {
    return m_layers.begin();
}

std::vector<Layer*>::iterator LayerStack::end() {
    return m_layers.end();
}
