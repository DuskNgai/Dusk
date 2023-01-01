#ifndef _DUSK_CORE_APPLICATION_LAYER_STACK_HPP_
#define _DUSK_CORE_APPLICATION_LAYER_STACK_HPP_

#include <vector>

#include <Dusk/Core/Application/Layer.hpp>

DUSK_NAMESPACE_BEGIN

/// @class An abstract class for storing layers.
/// The layers in layer stack will be executed in forward and backward order.
class LayerStack {
private:
    std::vector<Layer*> m_layers;
    std::size_t m_insert_index{0};

public:
    LayerStack() = default;
    ~LayerStack();

public:
    /// @brief Push back the layer, but before the overlay layers.
    void PushLayer(Layer* layer);

    /// @brief Push back the overlay layer.
    void PushOverlay(Layer* layer);

    /// @brief Pop out the given layer except it is at the back of the layers.
    /// It just removes the layer from the stack, disable the functionality of the layer.
    void PopLayer(Layer* layer);

    /// @brief Pop out the given overlay layer except it is at the back of the overlay layers.
    /// It just removes the overlay layer from the stack, disable the functionality of the overlay layer.
    void PopOverlay(Layer* layer);

    std::vector<Layer*>::iterator begin();
    std::vector<Layer*>::iterator end();
    std::vector<Layer*>::const_iterator begin() const;
    std::vector<Layer*>::const_iterator end() const;

    std::vector<Layer*>::reverse_iterator rbegin();
    std::vector<Layer*>::reverse_iterator rend();
    std::vector<Layer*>::const_reverse_iterator rbegin() const;
    std::vector<Layer*>::const_reverse_iterator rend() const;
};

DUSK_NAMESPACE_END

#endif // !_DUSK_CORE_APPLICATION_LAYER_STACK_HPP_
