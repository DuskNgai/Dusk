#ifndef _DUSK_CORE_EVENT_MOUSE_EVENT_HPP_
#define _DUSK_CORE_EVENT_MOUSE_EVENT_HPP_

#include <dusk/core/event/event.hpp>
#include <dusk/utils/mouse-code.hpp>

DUSK_NAMESPACE_BEGIN

/// @brief Base class for mouse events.
/// Derived classes are in the category of `Input` or `Mouse`.
class MouseMovedEvent : public EventBase {
private:
    float m_x, m_y;

public:
    MouseMovedEvent(float x, float y);

public:
    /// @return Gets the mouse position x in [0, W].
    float get_x() const;

    /// @return Gets the mouse position y in [0, W].
    float get_y() const;

    DUSK_EVENT_CATEGORY(EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput);
    DUSK_EVENT_TYPE(EventType::MouseMoved);
    virtual std::string to_string() const override;
};

/// @brief: The base class for event that are related to mouse scroll events.
/// The class derived from this class is in the category of `Mouse` and `Input`.
/// @see `EventBase`
class MouseScrolledEvent : public EventBase {
private:
    float m_offset_x, m_offset_y;

public:
    MouseScrolledEvent(float x, float y);

public:
    /// @return Gets the mouse scroll offset x.
    float get_offset_x() const;

    /// @return Gets the mouse scroll offset y.
    float get_offset_y() const;

    DUSK_EVENT_CATEGORY(EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput);
    DUSK_EVENT_TYPE(EventType::MouseScrolled);
    virtual std::string to_string() const override;
};

/// @brief Base clas for mouse button event.
/// Derived classes are in the category of `Input` or `Mouse` or `MouseButton`.
class MouseButtonEvent : public EventBase {
protected:
    MouseCode m_mouse_code;

public:
    MouseButtonEvent(MouseCode mouse_code);

public:
    MouseCode get_mouse_code() const;

    DUSK_EVENT_CATEGORY(EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput | EventCategory::EventCategoryMouseButton);
};

class MouseButtonPressedEvent : public MouseButtonEvent {
public:
    using MouseButtonEvent::MouseButtonEvent;

public:
    DUSK_EVENT_TYPE(EventType::MouseButtonPressed);
    virtual std::string to_string() const override;
};

class MouseButtonReleasedEvent : public MouseButtonEvent {
public:
    using MouseButtonEvent::MouseButtonEvent;

public:
    DUSK_EVENT_TYPE(EventType::MouseButtonReleased);
    virtual std::string to_string() const override;
};

DUSK_NAMESPACE_END

#endif // !_DUSK_CORE_EVENT_MOUSE_EVENT_HPP_
