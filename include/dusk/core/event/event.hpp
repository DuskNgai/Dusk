#ifndef _DUSK_CORE_EVENT_EVENT_HPP_
#define _DUSK_CORE_EVENT_EVENT_HPP_

#include <string>

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

/// @brief: Base of all the events.
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

    /// @brief Checks if the event belongs to the given `EventCategory`.
    bool is_in_category(EventCategory category) const;

    /// @brief Checks if the event is handled.
    bool is_handled() const;

    /// @brief Marks the event as handled.
    /// If the event is handled, it will not change the handled state.
    void mark_as_handled(bool is_handled);
};

#define DUSK_EVENT_CATEGORY(EVENT_CATEGORY_NAME) \
    virtual int get_category_flags() const override { return EVENT_CATEGORY_NAME; }

#define DUSK_EVENT_TYPE(EVENT_TYPE_NAME)                                                  \
    static EventType get_static_type() { return EVENT_TYPE_NAME; }                        \
    virtual EventType get_event_type() const override { return this->get_static_type(); } \
    virtual char const* get_name() const override { return #EVENT_TYPE_NAME; }

DUSK_NAMESPACE_END

#endif // !_DUSK_CORE_EVENT_EVENT_HPP_
