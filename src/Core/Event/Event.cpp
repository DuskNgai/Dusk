#include <Dusk/Core/Event/Event.hpp>

DUSK_NAMESPACE_BEGIN

std::string EventBase::ToString() const {
    return this->GetName();
}

bool EventBase::IsInCategory(EventCategory category) const {
    return (this->GetCategoryFlags() & category) != EventCategory::None;
}

EventDispatcher::EventDispatcher(EventBase& event)
    : m_event{event} {}

DUSK_NAMESPACE_END
