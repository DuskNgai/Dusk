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
    this->m_layers.emplace(this->begin() + this->m_insert_index, layer);
    this->m_insert_index++;
}

void LayerStack::push_overlay(Layer* layer) {
    this->m_layers.emplace_back(layer);
}

void LayerStack::pop_layer(Layer* layer) {
    // Find the layer in the stack with range [begin, m_insert_index).
    auto it{ std::find(this->begin(), this->begin() + this->m_insert_index, layer) };
    if (it != this->begin() + this->m_insert_index) {
        layer->on_detach();
        this->m_layers.erase(it);
        this->m_insert_index--;
    }
}

void LayerStack::pop_overlay(Layer* layer) {
    // Find the overlay layer in the stack with range [m_insert_index, end).
    auto it{ std::find(this->begin() + this->m_insert_index, this->end(), layer) };
    if (it != this->end()) {
        layer->on_detach();
        this->m_layers.erase(it);
    }
}

std::vector<Layer*>::iterator LayerStack::begin() { return this->m_layers.begin(); }
std::vector<Layer*>::iterator LayerStack::end() { return this->m_layers.end(); }
std::vector<Layer*>::const_iterator LayerStack::begin() const { return this->m_layers.begin(); }
std::vector<Layer*>::const_iterator LayerStack::end() const { return this->m_layers.end(); }

std::vector<Layer*>::reverse_iterator LayerStack::rbegin() { return this->m_layers.rbegin(); }
std::vector<Layer*>::reverse_iterator LayerStack::rend() { return this->m_layers.rend(); }
std::vector<Layer*>::const_reverse_iterator LayerStack::rbegin() const { return this->m_layers.rbegin(); }
std::vector<Layer*>::const_reverse_iterator LayerStack::rend() const { return this->m_layers.rend(); }

DUSK_NAMESPACE_END
