#ifndef _DUSK_CORE_APPLICATION_LAYER_STACK_HPP_
#define _DUSK_CORE_APPLICATION_LAYER_STACK_HPP_

#include <vector>

#include <dusk/core/application/layer.hpp>

DUSK_NAMESPACE_BEGIN

/// @class An abstract class for storing layers.
/// The layers in layer stack will be executed in forward and backward order.
class LayerStack {
private:
    std::vector<Layer*> m_layers;
    std::size_t m_insert_index{ 0 };

public:
    LayerStack() = default;
    ~LayerStack();

public:
    /// @brief Push back the layer, but before the overlay layers.
    void push_layer(Layer* layer);

    /// @brief Push back the overlay layer.
    void push_overlay(Layer* layer);

    /// @brief Pop out the given layer except it is at the back of the layers.
    /// It just removes the layer from the stack, disable the functionality of the layer.
    void pop_layer(Layer* layer);

    /// @brief Pop out the given overlay layer except it is at the back of the overlay layers.
    /// It just removes the overlay layer from the stack, disable the functionality of the overlay layer.
    void pop_overlay(Layer* layer);

    auto layer_end() { return this->m_layers.begin() + this->m_insert_index; }
    auto overlay_begin() { return this->layer_end(); }

    auto begin() { return this->m_layers.begin(); }
    auto end() { return this->m_layers.end(); }

    auto rbegin() { return this->m_layers.rbegin(); }
    auto rend() { return this->m_layers.rend(); }
};

DUSK_NAMESPACE_END

#endif // !_DUSK_CORE_APPLICATION_LAYER_STACK_HPP_
