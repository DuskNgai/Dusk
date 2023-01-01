#include <Dusk/Core/Event/KeyEvent.hpp>

DUSK_NAMESPACE_BEGIN

//! KeyEvent
KeyEvent::KeyEvent(KeyCode key_code)
    : m_key_code(key_code) {}

KeyCode KeyEvent::GetKeyCode() const { return this->m_key_code; }
//! KeyEvent

//! KeyPressedEvent
KeyPressedEvent::KeyPressedEvent(KeyCode key_code, bool is_repeat)
    : KeyEvent{key_code}
    , m_is_repeat{is_repeat} {}

bool KeyPressedEvent::IsRepeat() const { return this->m_is_repeat; }

std::string KeyPressedEvent::ToString() const {
    std::stringstream ss;
    ss << "KeyPressedEvent: " << static_cast<int>(this->m_key_code) << " (repeat = " << this->IsRepeat() << ")";
    return ss.str();
}
//! KeyPressedEvent

//! KeyReleasedEvent
std::string KeyReleasedEvent::ToString() const {
    std::stringstream ss;
    ss << "KeyReleasedEvent: " << static_cast<int>(this->GetKeyCode());
    return ss.str();
}
//! KeyReleasedEvent

//! KeyTypedEvent
std::string KeyTypedEvent::ToString() const {
    std::stringstream ss;
    ss << "KeyTypedEvent: " << static_cast<int>(this->GetKeyCode());
    return ss.str();
}
//! KeyTypedEvent

DUSK_NAMESPACE_END
