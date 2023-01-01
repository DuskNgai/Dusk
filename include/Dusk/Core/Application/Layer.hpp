#ifndef _DUSK_CORE_APPLICATION_LAYER_HPP_
#define _DUSK_CORE_APPLICATION_LAYER_HPP_

#include <Dusk/Core/Event/Event.hpp>

DUSK_NAMESPACE_BEGIN

/// @class Base class for layers.
/// Override this class to set your own logic.
class Layer {
protected:
    std::string m_debug_name;

public:
    Layer(std::string const& name = "Layer");
    virtual ~Layer() = default;

public:
    /// @brief A constructor that should be triggered once upon a layer is created.
    virtual void OnAttach();

    /// @brief A destructor that should be triggered once upon a layer is destroyed.
    virtual void OnDetach();

    /// @brief Update the everything in this layer with the current state.
    virtual void OnUpdate();

    /// @brief If a layer contains a ImGui layer, it should render all they need.
    virtual void OnImGuiRender();

    /// @brief Dealing with the event dispatched by the `Application`.
    virtual void OnEvent(EventBase& e);

    /// @brief The layer name used for debugging.
    std::string const& GetName() const;
};

DUSK_NAMESPACE_END

#endif // !_DUSK_CORE_APPLICATION_LAYER_HPP_
