#include <fmt/core.h>

#include <dusk/core/event/mouse-event.hpp>

DUSK_NAMESPACE_BEGIN

//! MouseMovedEvent
MouseMovedEvent::MouseMovedEvent(float x, float y)
    : m_x{ x }
    , m_y{ y } {}

float MouseMovedEvent::get_x() const {
    return this->m_x;
}

float MouseMovedEvent::get_y() const {
    return this->m_y;
}

std::string MouseMovedEvent::to_string() const {
    return fmt::format("MouseMovedEvent: ({:.6f}, {:.6f})", this->get_x(), this->get_y());
}
//! MouseMovedEvent

//! MouseScrolledEvent
MouseScrolledEvent::MouseScrolledEvent(float x, float y)
    : m_offset_x{ x }
    , m_offset_y{ y } {}

float MouseScrolledEvent::get_offset_x() const { return this->m_offset_x; }

float MouseScrolledEvent::get_offset_y() const { return this->m_offset_y; }

std::string MouseScrolledEvent::to_string() const {
    return fmt::format("MouseScrolledEvent: ({:.6f}, {:.6f})", this->get_offset_x(), this->get_offset_y());
}
//! MouseScrolledEvent

//! MouseButtonEvent
MouseButtonEvent::MouseButtonEvent(MouseCode mouse_code)
    : m_mouse_code{ mouse_code } {}

MouseCode MouseButtonEvent::get_mouse_code() const { return this->m_mouse_code; }
//! MouseButtonEvent

//! MouseButtonPressedEvent
std::string MouseButtonPressedEvent::to_string() const {
    return fmt::format("MouseButtonPressEvent: {:d}", static_cast<uint32_t>(this->get_mouse_code()));
}
//! MouseButtonPressedEvent

//! MouseButtonReleasedEvent
std::string MouseButtonReleasedEvent::to_string() const {
    return fmt::format("MouseButtonReleaseEvent: {:d}", static_cast<uint32_t>(this->get_mouse_code()));
}
//! MouseButtonReleasedEvent

DUSK_NAMESPACE_END
