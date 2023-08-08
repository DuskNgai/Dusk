#ifndef _DUSK_CORE_EVENT_EVENT_DISPATCHER_HPP_
#define _DUSK_CORE_EVENT_EVENT_DISPATCHER_HPP_

#include <dusk/core/event/event.hpp>

DUSK_NAMESPACE_BEGIN

/// @brief: Dispatch the event to a given function.
class EventDispatcher {
private:
    EventBase& m_event;

public:
    explicit EventDispatcher(EventBase& event)
        : m_event(event) {}

    /// @brief Dispatch the event to a given callback function.
    /// @tparam Func Usually a member function, returns `bool` as the handled state.
    /// @tparam EventType The type of the event to dispatch.
    template <typename Event, typename Func>
    bool dispatch(Func const& func) {
        if (this->m_event.get_event_type() == Event::get_static_type()) {
            this->m_event.mark_as_handled(func(static_cast<Event&>(this->m_event)));
            return true;
        }
        return false;
    }
};

DUSK_NAMESPACE_END

#endif // _DUSK_CORE_EVENT_EVENT_DISPATCHER_HPP_
