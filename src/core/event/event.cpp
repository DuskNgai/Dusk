#include <dusk/core/event/event.hpp>

DUSK_NAMESPACE_BEGIN

std::string EventBase::to_string() const {
    return this->get_name();
}

bool EventBase::is_in_category(EventCategory category) const {
    return (this->get_category_flags() & category) != EventCategory::None;
}

bool EventBase::is_handled() const {
    return this->m_handled;
}

void EventBase::mark_as_handled(bool is_handled) {
    this->m_handled |= is_handled;
}

DUSK_NAMESPACE_END
