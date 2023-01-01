#include <Dusk/Core/Event/MouseEvent.hpp>

DUSK_NAMESPACE_BEGIN

//! MouseMovedEvent
MouseMovedEvent::MouseMovedEvent(float x, float y)
    : m_mouse_x{x}
    , m_mouse_y{y} {}

float MouseMovedEvent::GetX() const { return this->m_mouse_x; }

float MouseMovedEvent::GetY() const { return this->m_mouse_y; }

std::string MouseMovedEvent::ToString() const {
    std::stringstream ss;
    ss << "MouseMovedEvent: [" << this->GetX() << ", " << this->GetY() << "]";
    return ss.str();
}
//! MouseMovedEvent

//! MouseScrolledEvent
MouseScrolledEvent::MouseScrolledEvent(float x, float y)
    : m_offset_x{x}
    , m_offset_y{y} {}

float MouseScrolledEvent::GetXOffset() const { return this->m_offset_x; }

float MouseScrolledEvent::GetYOffset() const { return this->m_offset_y; }

std::string MouseScrolledEvent::ToString() const {
    std::stringstream ss;
    ss << "MouseScrolledEvent: [" << this->GetXOffset() << ", " << this->GetYOffset() << "]";
    return ss.str();
}
//! MouseScrolledEvent

//! MouseButtonEvent
MouseButtonEvent::MouseButtonEvent(MouseCode button)
    : m_button{button} {}

MouseCode MouseButtonEvent::GetMouseButton() const { return this->m_button; }
//! MouseButtonEvent

//! MouseButtonPressedEvent
std::string MouseButtonPressedEvent::ToString() const {
    std::stringstream ss;
    ss << "MouseButtonPressedEvent: " << static_cast<int>(this->GetMouseButton());
    return ss.str();
}
//! MouseButtonPressedEvent

//! MouseButtonReleasedEvent
std::string MouseButtonReleasedEvent::ToString() const {
    std::stringstream ss;
    ss << "MouseButtonReleasedEvent: " << static_cast<int>(this->GetMouseButton());
    return ss.str();
}
//! MouseButtonReleasedEvent

DUSK_NAMESPACE_END
