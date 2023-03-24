#include <dusk/core/event/event.hpp>

DUSK_NAMESPACE_BEGIN

std::string EventBase::to_string() const {
    return this->get_name();
}

bool EventBase::is_in_category(EventCategory category) const {
    return (this->get_category_flags() & category) != EventCategory::None;
}

EventDispatcher::EventDispatcher(EventBase& event)
    : m_event{ event } {}

DUSK_NAMESPACE_END
