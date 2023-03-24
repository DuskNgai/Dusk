#ifndef _DUSK_CORE_APPLICATION_APPLICATION_HPP_
#define _DUSK_CORE_APPLICATION_APPLICATION_HPP_

#include <dusk/core/application/ImGui-layer.hpp>
#include <dusk/core/application/layer-stack.hpp>
#include <dusk/core/event/key-event.hpp>
#include <dusk/core/event/window-event.hpp>
#include <dusk/core/window/window-base.hpp>

DUSK_NAMESPACE_BEGIN

/// @class Application
/// @brief The base class for applications whom requires
/// a window and interactive operations.
/// One can consider this class as a shell.
/// Override this class to set your own flow of the application.
class Application {
protected:
    static Application* s_instance;
    std::unique_ptr<WindowBase> m_window;
    /// @brief A special layer for managing the ImGui.
    ImGuiLayer* m_imgui_layer;
    LayerStack m_layer_stack;
    bool m_is_running{ true };

public:
    Application();
    virtual ~Application();

public:
    /// @brief Push a layer to layer stack.
    virtual void push_layer(Layer* layer);

    /// @brief Push an overlaying layer to layer stack.
    /// Overlaying layers are always executed last in order to be shown on the top of the screen.
    virtual void push_overlay(Layer* layer);

    /// @brief Pop a layer from layer stack.
    virtual void pop_layer(Layer* layer);

    /// @brief Pop an overlaying layer from layer stack.
    virtual void pop_overlay(Layer* layer);

    /// @brief Execute/Update the states of layers in layer stack.
    /// Demostrate them on the screen if required.
    virtual void run();

    /// @brief Dispatch the event to each of the layers in layer stack.
    /// Also, there are some kinds of events should be dealt by this application.
    virtual void on_event(EventBase& e);

public:
    /// @brief The interface for getting this application.
    /// @return The pointer to this application.
    static Application* get();

    /// @brief Get the current window of this application.
    /// @return The pointer to the window.
    WindowBase* get_window();

    /// @brief Get the ImGui layer of this application.
    /// @return The pointer to the ImGui layer.
    ImGuiLayer* get_imgui_layer();

private:
    /// @brief Things that need to be done when there is a `WindowCloseEvent`.
    /// @return Whether the event is handled.
    bool on_window_close(WindowCloseEvent& e);

    /// @brief Things that need to be done when there is a `WindowResizeEvent`.
    /// @return Whether the event is handled.
    bool on_window_resize(WindowResizeEvent& e);

    /// @brief Things that need to be done when there is a `KeyPressedEvent`.
    /// @return Whether the event is handled.
    bool on_key_pressed(KeyPressedEvent& e);
};

DUSK_NAMESPACE_END

#endif // !_DUSK_CORE_APPLICATION_APPLICATION_HPP_
