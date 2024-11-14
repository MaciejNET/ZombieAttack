#ifndef EVENTBUS_HPP
#define EVENTBUS_HPP
#include <functional>

#include "Event.hpp"

namespace Events {
    class EventBus
    {
    public:
        EventBus() = delete;
        ~EventBus() = delete;

        EventBus(const EventBus&) = delete;
        EventBus& operator=(const EventBus&) = delete;
        template<typename T, typename = std::enable_if_t<std::is_base_of_v<Event, T>>>
        static void Subscribe(std::function<void(T&)> func)
        {
            _handlers[T().GetType()].push_back([func](Event& event) { func(static_cast<T&>(event)); });
        }
        template<typename T, typename = std::enable_if_t<std::is_base_of_v<Event, T>>>
        static void Unsubscribe()
        {
            auto eventType = T().GetType();
            auto it = _handlers.find(eventType);
            if (it != _handlers.end())
                it->second.clear();
        }
        static void Publish(const std::shared_ptr<Event>& event);
        static void DispatchEvents();
    private:
        static void DispatchEvent(Event& event);

    private:
        static std::unordered_map<EventType, std::vector<std::function<void(Event&)>>> _handlers;
        static std::vector<std::shared_ptr<Event>> _events;
    };
}

#endif //EVENTBUS_HPP
