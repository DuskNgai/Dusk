#include <dusk/core/event/window-event.hpp>

DUSK_NAMESPACE_BEGIN

//! WindowResizeEvent
WindowResizeEvent::WindowResizeEvent(uint32_t width, uint32_t height)
    : m_width{ width }
    , m_height{ height } {}

uint32_t WindowResizeEvent::get_width() const { return this->m_width; }

uint32_t WindowResizeEvent::get_height() const { return this->m_height; }

std::string WindowResizeEvent::to_string() const {
    std::stringstream ss;
    ss << "WindowResizeEvent: [" << this->get_width() << ", " << this->get_height() << "]";
    return ss.str();
}
//! WindowResizeEvent

DUSK_NAMESPACE_END
