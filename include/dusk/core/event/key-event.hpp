#ifndef _DUSK_CORE_EVENT_KEY_EVENT_HPP_
#define _DUSK_CORE_EVENT_KEY_EVENT_HPP_

#include <dusk/core/event/event.hpp>
#include <dusk/utils/key-code.hpp>

DUSK_NAMESPACE_BEGIN

/// @brief Base class for key events.
/// Derived classes are in the category of `Input` or `Keyboard`.
class KeyEvent : public EventBase {
protected:
    KeyCode m_key_code;

public:
    explicit KeyEvent(KeyCode key_code);

public:
    /// @return Get the current key code.
    KeyCode get_key_code() const;
    DUSK_EVENT_CATEGORY(EventCategory::EventCategoryInput | EventCategory::EventCategoryKeyboard);
};

class KeyPressedEvent : public KeyEvent {
private:
    bool m_is_repeat;

public:
    explicit KeyPressedEvent(KeyCode key_code, bool is_repeat = false);

public:
    bool is_repeat() const;
    DUSK_EVENT_TYPE(EventType::KeyPressed);
    virtual std::string to_string() const override;
};

class KeyReleasedEvent : public KeyEvent {
public:
    using KeyEvent::KeyEvent;

public:
    DUSK_EVENT_TYPE(EventType::KeyReleased);
    virtual std::string to_string() const override;
};

class KeyTypedEvent : public KeyEvent {
public:
    using KeyEvent::KeyEvent;

public:
    DUSK_EVENT_TYPE(EventType::KeyTyped);
    virtual std::string to_string() const override;
};

DUSK_NAMESPACE_END

#endif // !_DUSK_CORE_EVENT_KEY_EVENT_HPP_
