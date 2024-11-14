#ifndef KEYPRESSEDEVENT_HPP
#define KEYPRESSEDEVENT_HPP
#include "Event.hpp"

namespace Events {
    class KeyPressedEvent final : public Event
    {
    public:
        KeyPressedEvent() = default;
        explicit KeyPressedEvent(int key) : _key(key) {};
        const EventType GetType() const override { return EventType::KeyPressed; }
        int GetKey() const { return _key; }

    private:
        int _key{};
    };
}

#endif //KEYPRESSEDEVENT_HPP
