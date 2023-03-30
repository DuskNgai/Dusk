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
    virtual void push_layer(Layer* layer);

    /// @brief Overlaying layers are always executed last in order to be shown on the top of the screen.
    virtual void push_overlay(Layer* layer);

    virtual void pop_layer(Layer* layer);

    virtual void pop_overlay(Layer* layer);

    virtual void run();

    /// @brief Dispatch the event to each of the layers in layer stack.
    virtual void on_event(EventBase& e);

public:
    static Application* get();

    WindowBase* get_window();

    ImGuiLayer* get_imgui_layer();

private:
    bool on_window_close(WindowCloseEvent& e);

    bool on_window_resize(WindowResizeEvent& e);

    bool on_key_pressed(KeyPressedEvent& e);
};

DUSK_NAMESPACE_END

#endif // !_DUSK_CORE_APPLICATION_APPLICATION_HPP_
