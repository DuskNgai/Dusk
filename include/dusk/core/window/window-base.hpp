#ifndef _DUSK_WINDOW_WINDOW_BASE_HPP_
#define _DUSK_WINDOW_WINDOW_BASE_HPP_

#include <functional>
#include <memory>

#include "dusk/common.hpp"
#include "dusk/core/event/event.hpp"
#include "dusk/core/window/window-props.hpp"

DUSK_NAMESPACE_BEGIN

/// @class: Base class for all the windows in different platforms.
class WindowBase {
public:
    using EventCallbackFunc = std::function<void(EventBase&)>;

public:
    virtual ~WindowBase() = default;

public:
    virtual uint32_t get_width() const = 0;
    virtual uint32_t get_height() const = 0;
    virtual void* get_window_raw_ptr() const = 0;

    virtual void set_event_callback(EventCallbackFunc callback) = 0;

    virtual void set_vert_sync(bool enabled) = 0;

    virtual bool is_vert_sync() const = 0;

    /// @brief Update the window based on the current state of the window.
    /// This will be triggered after all the layers have been updated.
    virtual void on_update() = 0;

    /// @brief Create a window based on the given properties.
    static std::unique_ptr<WindowBase> create(WindowProps const& props = WindowProps{});
};

DUSK_NAMESPACE_END

#endif // !_DUSK_WINDOW_WINDOW_BASE_HPP_
