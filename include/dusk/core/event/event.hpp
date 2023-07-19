#ifndef _DUSK_CORE_EVENT_EVENT_HPP_
#define _DUSK_CORE_EVENT_EVENT_HPP_

#include <cstddef>
#include <iostream>
#include <sstream>

#include <dusk/common.hpp>

DUSK_NAMESPACE_BEGIN

// Events system are currently blocking, meaning when an event occurs it
// immediately gets dispatched and must be dealt with right then an there.
// For the future, a better strategy might be to buffer events in an event
// bus and process them during the "event" part of the update stage.

// The category of all the events.
// clang-format off
enum EventCategory {
    None                     = 0,
    EventCategoryApplication = (1 << 0),
    EventCategoryInput       = (1 << 1),
    EventCategoryKeyboard    = (1 << 2),
    EventCategoryMouse       = (1 << 3),
    EventCategoryMouseButton = (1 << 4)
};

// The specific type of all the events.
// One event type may be in several categories.
enum class EventType : int32_t {
    None = 0,
    ApplicationTick, ApplicationRender, ApplicationUpdate,
    WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
    KeyPressed, KeyReleased, KeyTyped,
    MouseMoved, MouseScrolled, MouseButtonPressed, MouseButtonReleased
};
// clang-format on

/// @class: Base of all the events.
class EventBase {
public:
    bool m_handled{ false };

public:
    virtual ~EventBase() = default;

    /// @brief Get the `EventCategory` of a event.
    /// An event may be in several categories.
    virtual int get_category_flags() const = 0;

    /// @brief Get the `EventType` of a event.
    /// An event can only be in on type.
    virtual EventType get_event_type() const = 0;

    virtual char const* get_name() const = 0;

    /// @brief Get the details of a event.
    virtual std::string to_string() const;

    bool is_in_category(EventCategory category) const;
};

/// @class: Dispatch the event to a given function.
class EventDispatcher {
private:
    EventBase& m_event;

public:
    /// @param event: The event to be dispatched.
    explicit EventDispatcher(EventBase& event);

    /// @brief Dispatch the event to a given function.
    /// @param func: The function dealing with the event.
    /// @return: If the event is handled by the given function, then it will not be dealt by other functions.
    template <typename Event, typename Func>
    bool dispatch(Func const& func) {
        if (m_event.get_event_type() == Event::get_static_type()) {
            m_event.m_handled |= func(static_cast<Event&>(m_event));
            return true;
        }
        return false;
    }
};

#define DUSK_EVENT_CATEGORY(EVENT_CATEGORY_NAME) \
    virtual int get_category_flags() const override { return EVENT_CATEGORY_NAME; }

#define DUSK_EVENT_TYPE(EVENT_TYPE_NAME)                                                  \
    static EventType get_static_type() { return EVENT_TYPE_NAME; }                        \
    virtual EventType get_event_type() const override { return this->get_static_type(); } \
    virtual char const* get_name() const override { return #EVENT_TYPE_NAME; }

DUSK_NAMESPACE_END

#endif // !_DUSK_CORE_EVENT_EVENT_HPP_
