#ifndef _DUSK_WINDOW_WINDOW_HPP_
#define _DUSK_WINDOW_WINDOW_HPP_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Dusk/Core/Event/ApplicationEvent.hpp>
#include <Dusk/Core/Event/KeyEvent.hpp>
#include <Dusk/Core/Event/MouseEvent.hpp>
#include <Dusk/Core/Event/WindowEvent.hpp>
#include <Dusk/Core/Window/WindowBase.hpp>
#include <Dusk/Renderer/GraphicsContext.hpp>

DUSK_NAMESPACE_BEGIN

struct WindowData {
    WindowProps m_props{};
    WindowBase::EventCallbackFunc m_callback{};
    bool m_vert_sync{};
};

class Window : public WindowBase {
private:
    GLFWwindow* m_window;
    std::unique_ptr<GraphicsContext> m_context;
    WindowData m_data;

public:
    Window(WindowProps const& props);
    virtual ~Window();

public:
    virtual uint32_t GetWidth() const override;
    virtual uint32_t GetHeight() const override;
    virtual void* GetWindowRawPtr() const override;

    virtual void SetEventCallback(EventCallbackFunc callback) override;
    virtual void SetVertSync(bool enabled) override;
    virtual bool IsVertSync() const override;

    virtual void OnUpdate() override;

private:
    /// @brief Triggered in constructor.
    void Initialize(WindowProps const& props);
    /// @brief Triggered in destructor.
    void ShutDown();
};

DUSK_NAMESPACE_END

#endif // !_DUSK_WINDOW_WINDOW_HPP_
