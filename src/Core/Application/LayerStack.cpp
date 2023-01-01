#include <algorithm>

#include <Dusk/Core/Application/LayerStack.hpp>

DUSK_NAMESPACE_BEGIN

LayerStack::~LayerStack() {
    for (auto&& layer : this->m_layers) {
        layer->OnDetach();
        delete layer;
    }
}

void LayerStack::PushLayer(Layer* layer) {
    this->m_layers.emplace(this->begin() + this->m_insert_index, layer);
    this->m_insert_index++;
}

void LayerStack::PushOverlay(Layer* layer) {
    this->m_layers.emplace_back(layer);
}

void LayerStack::PopLayer(Layer* layer) {
    auto it = std::find(this->begin(), this->begin() + this->m_insert_index, layer);
    if (it != this->begin() + this->m_insert_index) {
        layer->OnDetach();
        this->m_layers.erase(it);
        this->m_insert_index--;
    }
}

void LayerStack::PopOverlay(Layer* layer) {
    auto it = std::find(this->begin() + this->m_insert_index, this->end(), layer);
    if (it != this->end()) {
        layer->OnDetach();
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
