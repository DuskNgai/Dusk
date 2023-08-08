#ifndef _DUSK_CORE_EVENT_WINDOW_EVENT_HPP_
#define _DUSK_CORE_EVENT_WINDOW_EVENT_HPP_

#include <dusk/core/event/event.hpp>

DUSK_NAMESPACE_BEGIN

/// @brief: The base class for event that are related to window events.
/// The class derived from this class is in the category of `Application`.
class WindowEvent : public EventBase {
public:
    WindowEvent() = default;

    DUSK_EVENT_CATEGORY(EventCategory::EventCategoryApplication);
};

class WindowResizeEvent : public WindowEvent {
private:
    uint32_t m_width, m_height;

public:
    WindowResizeEvent(uint32_t width, uint32_t height);

public:
    uint32_t get_width() const;
    uint32_t get_height() const;

    DUSK_EVENT_TYPE(EventType::WindowResize);
    virtual std::string to_string() const override;
};

class WindowCloseEvent : public WindowEvent {
public:
    WindowCloseEvent() = default;

public:
    DUSK_EVENT_TYPE(EventType::WindowClose);
};

DUSK_NAMESPACE_END

#endif // !_DUSK_CORE_EVENT_WINDOW_EVENT_HPP_
