#ifndef _DUSK_CORE_APPLICATION_LAYER_HPP_
#define _DUSK_CORE_APPLICATION_LAYER_HPP_

#include <dusk/core/event/event.hpp>

DUSK_NAMESPACE_BEGIN

/// @brief Base class for layers.
/// One can consider this class as a execution core.
/// Override this class to set your own logic.
class Layer {
protected:
    std::string m_debug_name;

public:
    Layer(std::string const& name = "Layer");
    virtual ~Layer() = default;

public:
    /// @brief A constructor that should be triggered once upon a layer is created.
    virtual void on_attach() = 0;

    /// @brief A destructor that should be triggered once upon a layer is destroyed.
    virtual void on_detach() = 0;

    /// @brief Update the everything in this layer with the current state.
    virtual void on_update() = 0;

    /// @brief If a layer contains a ImGui layer, it should render all they need.
    virtual void on_ImGui_render() = 0;

    /// @brief Dealing with the event dispatched by the `Application`.
    virtual void on_event(EventBase& e) = 0;

    std::string const& get_name() const;
};

DUSK_NAMESPACE_END

#endif // !_DUSK_CORE_APPLICATION_LAYER_HPP_
