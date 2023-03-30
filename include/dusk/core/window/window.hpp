#ifndef _DUSK_WINDOW_WINDOW_HPP_
#define _DUSK_WINDOW_WINDOW_HPP_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <dusk/core/event/application-event.hpp>
#include <dusk/core/event/key-event.hpp>
#include <dusk/core/event/mouse-event.hpp>
#include <dusk/core/event/window-event.hpp>
#include <dusk/core/window/window-base.hpp>
#include <dusk/renderer/graphics-context.hpp>

DUSK_NAMESPACE_BEGIN

class Window : public WindowBase {
private:
    GLFWwindow* m_window;
    std::unique_ptr<GraphicsContext> m_context;
    struct WindowData {
        WindowProps m_props{};
        WindowBase::EventCallbackFunc m_callback{ nullptr };
        bool m_vert_sync{ false };
    } m_data;

public:
    Window(WindowProps const& props);
    virtual ~Window();

public:
    virtual uint32_t get_width() const override;
    virtual uint32_t get_height() const override;
    virtual void* get_window_raw_ptr() const override;

    virtual void set_event_callback(EventCallbackFunc callback) override;
    virtual void set_vert_sync(bool enabled) override;
    virtual bool is_vert_sync() const override;

    /// @brief Poll events and swap buffers.
    virtual void on_update() override;

private:
    void init(WindowProps const& props);
    void shut_down();
};

DUSK_NAMESPACE_END

#endif // !_DUSK_WINDOW_WINDOW_HPP_
