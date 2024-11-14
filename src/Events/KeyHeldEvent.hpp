#ifndef KEYHELDEVENT_HPP
#define KEYHELDEVENT_HPP
#include "Event.hpp"

namespace Events {
    class KeyHeldEvent final : public Event
    {
    public:
        KeyHeldEvent() = default;
        explicit KeyHeldEvent(int key) : _key(key) {};
        const EventType GetType() const override { return EventType::KeyHeld; }
        int GetKey() const { return _key; }

    private:
        int _key{};
    };
}

#endif //KEYHELDEVENT_HPP
