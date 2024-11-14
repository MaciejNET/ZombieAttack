#ifndef MOUSEBUTTONPRESSEDEVENT_HPP
#define MOUSEBUTTONPRESSEDEVENT_HPP
#include "Event.hpp"

namespace Events {
    class MouseButtonPressedEvent final : public Event
    {
    public:
        MouseButtonPressedEvent(int button) : _button(button) {};
        const EventType GetType() const override { return EventType::MouseButtonPressed; };
        int GetButton() const { return _button; };

    private:
        int _button{};
    };
}

#endif //MOUSEBUTTONPRESSEDEVENT_HPP
