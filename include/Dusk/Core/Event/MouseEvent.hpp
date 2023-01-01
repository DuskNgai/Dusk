#ifndef _DUSK_CORE_EVENT_MOUSE_EVENT_HPP_
#define _DUSK_CORE_EVENT_MOUSE_EVENT_HPP_

#include <Dusk/Core/Event/Event.hpp>
#include <Dusk/Utils/MouseCode.hpp>

DUSK_NAMESPACE_BEGIN

/// @class: The base class for event that are related to mouse move events.
/// The class derived from this class is in the category of `Mouse` and `Input`.
/// @see `EventBase`
class MouseMovedEvent : public EventBase {
private:
    float m_mouse_x, m_mouse_y;

public:
    MouseMovedEvent(float x, float y);

public:
    // Get the current mouse position x.
    float GetX() const;
    // Get the current mouse position y.
    float GetY() const;

    DUSK_EVENT_CATEGORY(EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput);
    DUSK_EVENT_TYPE(EventType::MouseMoved);
    virtual std::string ToString() const override;
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
    // Get the current mouse offset x.
    float GetXOffset() const;
    // Get the current mouse offset y.
    float GetYOffset() const;

    DUSK_EVENT_CATEGORY(EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput);
    DUSK_EVENT_TYPE(EventType::MouseScrolled);
    virtual std::string ToString() const override;
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
    // Get the current mouse button code.
    MouseCode GetMouseButton() const;

    DUSK_EVENT_CATEGORY(EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput | EventCategory::EventCategoryMouseButton);
};

/// @see `MouseButtonEvent`
class MouseButtonPressedEvent : public MouseButtonEvent {
public:
    using MouseButtonEvent::MouseButtonEvent;

public:
    DUSK_EVENT_TYPE(EventType::MouseButtonPressed);
    virtual std::string ToString() const override;
};

/// @see `MouseButtonEvent`
class MouseButtonReleasedEvent : public MouseButtonEvent {
public:
    using MouseButtonEvent::MouseButtonEvent;

public:
    DUSK_EVENT_TYPE(EventType::MouseButtonReleased);
    virtual std::string ToString() const override;
};

DUSK_NAMESPACE_END

#endif // !_DUSK_CORE_EVENT_MOUSE_EVENT_HPP_
