#ifndef _DUSK_CORE_EVENT_APPLICATION_EVENT_HPP_
#define _DUSK_CORE_EVENT_APPLICATION_EVENT_HPP_

#include <dusk/core/event/event.hpp>

DUSK_NAMESPACE_BEGIN

/// @brief: The base class for event that are related to application events.
/// The class derived from this class is in the category of `Application`.
/// @see `EventBase`
class ApplicationEvent : public EventBase {
public:
    ApplicationEvent() = default;

    DUSK_EVENT_CATEGORY(EventCategory::EventCategoryApplication);
};

/// @see `ApplicationEvent`
class ApplicationTickEvent : public ApplicationEvent {
public:
    using ApplicationEvent::ApplicationEvent;

    DUSK_EVENT_TYPE(EventType::ApplicationTick);
};

/// @see `ApplicationEvent`
class AppliactionRenderEvent : public ApplicationEvent {
public:
    using ApplicationEvent::ApplicationEvent;

    DUSK_EVENT_TYPE(EventType::ApplicationRender);
};

/// @see `ApplicationEvent`
class AppliactionUpdateEvent : public ApplicationEvent {
public:
    using ApplicationEvent::ApplicationEvent;

    DUSK_EVENT_TYPE(EventType::ApplicationUpdate);
};

DUSK_NAMESPACE_END

#endif // !_DUSK_CORE_EVENT_APPLICATION_EVENT_HPP_
