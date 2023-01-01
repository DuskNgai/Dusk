#ifndef _DUSK_WINDOW_WINDOW_BASE_HPP_
#define _DUSK_WINDOW_WINDOW_BASE_HPP_

#include <functional>
#include <memory>

#include "Dusk/Common.hpp"
#include "Dusk/Core/Event/Event.hpp"

DUSK_NAMESPACE_BEGIN

struct WindowProps {
    uint32_t m_width{1920};
    uint32_t m_height{1080};
    std::string m_title{"Dusk-Engine"};
};

/// @class: Base class for all the windows in different platforms.
class WindowBase {
public:
    using EventCallbackFunc = std::function<void(EventBase&)>;

public:
    virtual ~WindowBase() = default;

public:
    /// @return The width of the window.
    virtual uint32_t GetWidth() const = 0;

    /// @return The height of the window.
    virtual uint32_t GetHeight() const = 0;

    /// @return The raw pointer of the window.
    virtual void* GetWindowRawPtr() const = 0;

    /// @brief Set the callback function for the window.
    virtual void SetEventCallback(EventCallbackFunc callback) = 0;

    /// @brief Enable vertical synchronization.
    virtual void SetVertSync(bool enabled) = 0;

    /// @return Is vertical synchronization.
    virtual bool IsVertSync() const = 0;

    /// @brief Update the window based on the current state of the window.
    /// This will be triggered after all the layers have been updated.
    virtual void OnUpdate() = 0;

    static std::unique_ptr<WindowBase> Create(WindowProps const& props = WindowProps{});
};

DUSK_NAMESPACE_END

#endif // !_DUSK_WINDOW_WINDOW_BASE_HPP_
