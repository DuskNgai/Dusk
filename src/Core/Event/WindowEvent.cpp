#include <Dusk/Core/Event/WindowEvent.hpp>

DUSK_NAMESPACE_BEGIN

//! WindowResizeEvent
WindowResizeEvent::WindowResizeEvent(uint32_t width, uint32_t height)
    : m_width{width}
    , m_height{height} {}

uint32_t WindowResizeEvent::GetWidth() const { return this->m_width; }

uint32_t WindowResizeEvent::GetHeight() const { return this->m_height; }

std::string WindowResizeEvent::ToString() const {
    std::stringstream ss;
    ss << "WindowResizeEvent: [" << this->GetWidth() << ", " << this->GetHeight() << "]";
    return ss.str();
}
//! WindowResizeEvent

DUSK_NAMESPACE_END
