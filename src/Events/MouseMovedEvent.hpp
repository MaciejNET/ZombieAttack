#ifndef MOUSEMOVEDEVENT_HPP
#define MOUSEMOVEDEVENT_HPP
#include "Event.hpp"

namespace Events {
    class MouseMovedEvent final : public Event
    {
    public:
        MouseMovedEvent() = default;
        explicit MouseMovedEvent(float x, float y) : _x(x), _y(y) {};
        const EventType GetType() const override { return EventType::MouseMoved; }
        float GetX() const { return _x; }
        float GetY() const { return _y; }

    private:
        float _x{};
        float _y{};
    };
}

#endif //MOUSEMOVEDEVENT_HPP
