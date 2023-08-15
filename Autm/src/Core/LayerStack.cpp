#include "LayerStack.h"

LayerStack::LayerStack() {
    m_layer_insert = begin();
}

LayerStack::~LayerStack() {
    for (Layer* layer : m_layers) {
        delete layer;
    }
}

void LayerStack::push_layer(Layer* layer) {
    m_layer_insert = m_layers.emplace(m_layer_insert, layer);
}

void LayerStack::pop_layer(Layer* layer) {
    auto it = std::find(begin(), end(), layer);
    if (it != end()) {
        m_layers.erase(it);
        m_layer_insert--;
    }
}

void LayerStack::push_overlay(Layer* layer) {
    m_layers.emplace_back(layer);
}

void LayerStack::pop_overlay(Layer* layer) {
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
