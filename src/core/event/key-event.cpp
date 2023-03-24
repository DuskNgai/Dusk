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
    std::stringstream ss;
    ss << "KeyPressedEvent: " << static_cast<int>(this->get_key_code()) << " (repeat = " << this->is_repeat() << ")";
    return ss.str();
}
//! KeyPressedEvent

//! KeyReleasedEvent
std::string KeyReleasedEvent::to_string() const {
    std::stringstream ss;
    ss << "KeyReleasedEvent: " << static_cast<int>(this->get_key_code());
    return ss.str();
}
//! KeyReleasedEvent

//! KeyTypedEvent
std::string KeyTypedEvent::to_string() const {
    std::stringstream ss;
    ss << "KeyTypedEvent: " << static_cast<int>(this->get_key_code());
    return ss.str();
}
//! KeyTypedEvent

DUSK_NAMESPACE_END
