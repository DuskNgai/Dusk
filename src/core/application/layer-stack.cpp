#include <algorithm>

#include <dusk/core/application/layer-stack.hpp>

DUSK_NAMESPACE_BEGIN

LayerStack::~LayerStack() {
    // Delete all layers in the stack.
    // This function is called when the application is closed.
    for (auto&& layer : this->m_layers) {
        layer->on_detach();
        delete layer;
    }
}

void LayerStack::push_layer(Layer* layer) {
    // Insert the layer before the overlay layers.
    this->m_layers.emplace(this->layer_end(), layer);
    this->m_insert_index++;
    layer->on_attach();
}

void LayerStack::push_overlay(Layer* layer) {
    this->m_layers.emplace_back(layer);
    layer->on_attach();
}

void LayerStack::pop_layer(Layer* layer) {
    // Find the layer in the stack with range [begin, m_insert_index).
    auto it{ std::find(this->begin(), this->layer_end(), layer) };
    if (it != this->layer_end()) {
        layer->on_detach();
        this->m_layers.erase(it);
        this->m_insert_index--;
    }
}

void LayerStack::pop_overlay(Layer* layer) {
    // Find the overlay layer in the stack with range [m_insert_index, end).
    auto it{ std::find(this->overlay_begin(), this->end(), layer) };
    if (it != this->end()) {
        layer->on_detach();
        this->m_layers.erase(it);
    }
}

DUSK_NAMESPACE_END
