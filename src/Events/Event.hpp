#ifndef EVENT_HPP
#define EVENT_HPP

namespace Events {
    enum class EventType
    {
        None = 0,
        KeyPressed,
        MouseMoved,
        KeyHeld,
        KeyReleased,
        MouseButtonPressed
    };

    class Event
    {
    public:
        Event() = default;
        virtual ~Event() = default;
        virtual const EventType GetType() const = 0;
    };

}

#endif //EVENT_HPP
