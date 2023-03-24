#ifndef _DUSK_CORE_EVENT_MOUSE_EVENT_HPP_
#define _DUSK_CORE_EVENT_MOUSE_EVENT_HPP_

#include <dusk/core/event/event.hpp>
#include <dusk/core/utils/mouse-code.hpp>

DUSK_NAMESPACE_BEGIN

/// @class: The base class for event that are related to mouse move events.
/// The class derived from this class is in the category of `Mouse` and `Input`.
/// @see `EventBase`
class MouseMovedEvent : public EventBase {
private:
    float m_mouse_x, m_mouse_y, m_window_width, m_window_height;

public:
    MouseMovedEvent(float x, float y, float window_width, float window_height);

public:
    /// @return Get the current mouse position x.
    float get_x() const;
    /// @return Get the current mouse position y.
    float get_y() const;

    /// @return Get the current mouse position x in NDC.
    float get_ndc_x() const;
    /// @return Get the current mouse position y in NDC.
    float get_ndc_y() const;

    DUSK_EVENT_CATEGORY(EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput);
    DUSK_EVENT_TYPE(EventType::MouseMoved);
    virtual std::string to_string() const override;
};

/// @class: The base class for event that are related to mouse scroll events.
/// The class derived from this class is in the category of `Mouse` and `Input`.
/// @see `EventBase`
class MouseScrolledEvent : public EventBase {
private:
    float m_offset_x, m_offset_y;

public:
    MouseScrolledEvent(float x, float y);

public:
    /// @return Get the current mouse offset x.
    float get_offset_x() const;
    /// @return Get the current mouse offset y.
    float get_offset_y() const;

    DUSK_EVENT_CATEGORY(EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput);
    DUSK_EVENT_TYPE(EventType::MouseScrolled);
    virtual std::string to_string() const override;
};

/// @class: The base class for event that are related to mouse button events.
/// The class derived from this class is in the category of `Mouse`, `Input`, and `MouseButton`.
/// @see `EventBase`
class MouseButtonEvent : public EventBase {
protected:
    MouseCode m_button;

public:
    MouseButtonEvent(MouseCode button);

public:
    /// @return Get the current mouse button code.
    MouseCode get_mouse_button() const;

    DUSK_EVENT_CATEGORY(EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput | EventCategory::EventCategoryMouseButton);
};

/// @see `MouseButtonEvent`
class MouseButtonPressedEvent : public MouseButtonEvent {
public:
    using MouseButtonEvent::MouseButtonEvent;

public:
    DUSK_EVENT_TYPE(EventType::MouseButtonPressed);
    virtual std::string to_string() const override;
};

/// @see `MouseButtonEvent`
class MouseButtonReleasedEvent : public MouseButtonEvent {
public:
    using MouseButtonEvent::MouseButtonEvent;

public:
    DUSK_EVENT_TYPE(EventType::MouseButtonReleased);
    virtual std::string to_string() const override;
};

DUSK_NAMESPACE_END

#endif // !_DUSK_CORE_EVENT_MOUSE_EVENT_HPP_
