#ifndef _DUSK_CORE_APPLICATION_APPLICATION_HPP_
#define _DUSK_CORE_APPLICATION_APPLICATION_HPP_

#include <Dusk/Core/Application/ImGuiLayer.hpp>
#include <Dusk/Core/Application/LayerStack.hpp>
#include <Dusk/Core/Event/KeyEvent.hpp>
#include <Dusk/Core/Event/WindowEvent.hpp>
#include <Dusk/Core/Window/WindowBase.hpp>

DUSK_NAMESPACE_BEGIN

/// @class Application
/// @brief Base class for applications that need window and interactive operations.
/// Override this class to set your own flow of the application.
class Application {
protected:
    static Application* s_instance;
    std::unique_ptr<WindowBase> m_window;
    ImGuiLayer* m_imgui_layer;
    LayerStack m_layer_stack;
    bool m_is_running{true};

public:
    Application();
    virtual ~Application();

public:
    /// @brief Push a layer to layer stack.
    virtual void PushLayer(Layer* layer);

    /// @brief Push an overlaying layer to layer stack.
    /// Overlaying layers are always executed last but shown on the top of the screen.
    virtual void PushOverlay(Layer* layer);

    /// @brief Pop a layer from layer stack.
    virtual void PopLayer(Layer* layer);

    /// @brief Pop an overlaying layer from layer stack.
    virtual void PopOverlay(Layer* layer);

    /// @brief Execute/Update the layers in layer stack and shown them on the screen.
    virtual void Run();

    /// @brief Dispatch the event to each of the layers in layer stack.
    /// Also, there are some kinds of events should be dealt by this application.
    virtual void OnEvent(EventBase& e);

public:
    /// @brief The interface for getting this application.
    static Application* Get();

    /// @brief Get the current window of this application.
    WindowBase* GetWindow();

private:
    /// @brief Things that need to be done when there is a `WindowCloseEvent`.
    bool OnWindowClose(WindowCloseEvent& e);

    /// @brief Things that need to be done when there is a `WindowResizeEvent`.
    bool OnWindowResize(WindowResizeEvent& e);

    /// @brief Things that need to be done when there is a `WindowResizeEvent`.
    bool OnKeyPressed(KeyPressedEvent& e);
};

DUSK_NAMESPACE_END

#endif // !_DUSK_CORE_APPLICATION_APPLICATION_HPP_
