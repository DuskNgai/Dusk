#include <fmt/core.h>

#include <dusk/core/event/key-event.hpp>

DUSK_NAMESPACE_BEGIN

//! KeyEvent
KeyEvent::KeyEvent(KeyCode key_code)
    : m_key_code{ key_code } {}

KeyCode KeyEvent::get_key_code() const { return this->m_key_code; }
//! KeyEvent

//! KeyPressedEvent
KeyPressedEvent::KeyPressedEvent(KeyCode key_code, bool is_repeat)
    : KeyEvent{ key_code }
    , m_is_repeat{ is_repeat } {}

bool KeyPressedEvent::is_repeat() const { return this->m_is_repeat; }

std::string KeyPressedEvent::to_string() const {
    return fmt::format("KeyPressedEvent: {:d} (repeated = {})", static_cast<uint32_t>(this->get_key_code()), this->is_repeat());
}
//! KeyPressedEvent

//! KeyReleasedEvent
std::string KeyReleasedEvent::to_string() const {
    return fmt::format("KeyReleasedEvent: {:d}", static_cast<uint32_t>(this->get_key_code()));
}
//! KeyReleasedEvent

//! KeyTypedEvent
std::string KeyTypedEvent::to_string() const {
    return fmt::format("KeyTypedEvent: {:d}", static_cast<uint32_t>(this->get_key_code()));
}
//! KeyTypedEvent

DUSK_NAMESPACE_END
