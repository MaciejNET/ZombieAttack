#include <Events/EventBus.hpp>

namespace Events {
    std::unordered_map<EventType, std::vector<std::function<void(Event&)>>> EventBus::_handlers;
    std::vector<std::shared_ptr<Event>> EventBus::_events;

    void EventBus::Publish(const std::shared_ptr<Event>& event)
    {
        _events.push_back(event);
    }

    void EventBus::DispatchEvents()
    {
        for (auto& event : _events)
            DispatchEvent(*event);

        _events.clear();
    }

    void EventBus::DispatchEvent(Event& event)
    {
        for (auto& subscriber : _handlers[event.GetType()])
            subscriber(event);
    }
}