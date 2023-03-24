#include <dusk/core/event/mouse-event.hpp>

DUSK_NAMESPACE_BEGIN

//! MouseMovedEvent
MouseMovedEvent::MouseMovedEvent(float x, float y, float window_width, float window_height)
    : m_mouse_x{ x }
    , m_mouse_y{ y }
    , m_window_width{ window_width }
    , m_window_height{ window_height } {}

float MouseMovedEvent::get_x() const { return this->m_mouse_x; }

float MouseMovedEvent::get_y() const { return this->m_mouse_y; }

float MouseMovedEvent::get_ndc_x() const { return (this->get_x() / this->m_window_width) * 2.0f - 1.0f; }

float MouseMovedEvent::get_ndc_y() const { return (this->get_y() / this->m_window_height) * 2.0f - 1.0f; }

std::string MouseMovedEvent::to_string() const {
    std::stringstream ss;
    ss << "MouseMovedEvent: [" << this->get_x() << ", " << this->get_y() << "]";
    return ss.str();
}
//! MouseMovedEvent

//! MouseScrolledEvent
MouseScrolledEvent::MouseScrolledEvent(float x, float y)
    : m_offset_x{ x }
    , m_offset_y{ y } {}

float MouseScrolledEvent::get_offset_x() const { return this->m_offset_x; }

float MouseScrolledEvent::get_offset_y() const { return this->m_offset_y; }

std::string MouseScrolledEvent::to_string() const {
    std::stringstream ss;
    ss << "MouseScrolledEvent: [" << this->get_offset_x() << ", " << this->get_offset_y() << "]";
    return ss.str();
}
//! MouseScrolledEvent

//! MouseButtonEvent
MouseButtonEvent::MouseButtonEvent(MouseCode button)
    : m_button{ button } {}

MouseCode MouseButtonEvent::get_mouse_button() const { return this->m_button; }
//! MouseButtonEvent

//! MouseButtonPressedEvent
std::string MouseButtonPressedEvent::to_string() const {
    std::stringstream ss;
    ss << "MouseButtonPressedEvent: " << static_cast<int>(this->get_mouse_button());
    return ss.str();
}
//! MouseButtonPressedEvent

//! MouseButtonReleasedEvent
std::string MouseButtonReleasedEvent::to_string() const {
    std::stringstream ss;
    ss << "MouseButtonReleasedEvent: " << static_cast<int>(this->get_mouse_button());
    return ss.str();
}
//! MouseButtonReleasedEvent

DUSK_NAMESPACE_END
