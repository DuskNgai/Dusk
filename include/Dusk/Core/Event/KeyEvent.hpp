#ifndef _DUSK_CORE_EVENT_KEY_EVENT_HPP_
#define _DUSK_CORE_EVENT_KEY_EVENT_HPP_

#include <Dusk/Core/Event/Event.hpp>
#include <Dusk/Utils/KeyCode.hpp>

DUSK_NAMESPACE_BEGIN

/// @class: The base class for event that are related to keyboard events.
/// The class derived from this class is in the category of `Input` and `Keyboard`.
/// @see `EventBase`
class KeyEvent : public EventBase {
protected:
    KeyCode m_key_code;

public:
    explicit KeyEvent(KeyCode key_code);

public:
    KeyCode GetKeyCode() const;
    DUSK_EVENT_CATEGORY(EventCategory::EventCategoryInput | EventCategory::EventCategoryKeyboard);
};

/// @see `KeyEvent`
class KeyPressedEvent : public KeyEvent {
private:
    bool m_is_repeat;

public:
    explicit KeyPressedEvent(KeyCode key_code, bool is_repeat = false);

public:
    bool IsRepeat() const;
    DUSK_EVENT_TYPE(EventType::KeyPressed);
    virtual std::string ToString() const override;
};

/// @see `KeyEvent`
class KeyReleasedEvent : public KeyEvent {
public:
    using KeyEvent::KeyEvent;

public:
    DUSK_EVENT_TYPE(EventType::KeyReleased);
    virtual std::string ToString() const override;
};

/// @see `KeyEvent`
class KeyTypedEvent : public KeyEvent {
public:
    using KeyEvent::KeyEvent;

public:
    DUSK_EVENT_TYPE(EventType::KeyTyped);
    virtual std::string ToString() const override;
};

DUSK_NAMESPACE_END

#endif // !_DUSK_CORE_EVENT_KEY_EVENT_HPP_
