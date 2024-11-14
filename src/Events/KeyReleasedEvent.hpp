#ifndef KEYRELEASEDEVENT_HPP
#define KEYRELEASEDEVENT_HPP
#include "Event.hpp"

namespace Events {
    class KeyReleasedEvent final : public Event
    {
    public:
        KeyReleasedEvent() = default;
        KeyReleasedEvent(int key) : _key(key) {};
        const EventType GetType() const override { return EventType::KeyReleased; };
        int GetKey() const { return _key; };

    private:
        int _key{};
    };
}

#endif //KEYRELEASEDEVENT_HPP
