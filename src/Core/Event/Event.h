#ifndef AUTM_EVENT_H
#define AUTM_EVENT_H

#include "autmpch.h"

#define BIND_EVENT_FUNCTION(x) std::bind(&x, this, std::placeholders::_1)

enum class EventType {
    None = 0, MouseButtonPressed = 1, MouseButtonReleased = 2, MouseMoved = 3, MouseScrolled = 4, KeyPressed = 5, KeyReleased = 6, WindowResizedEvent
};

class Event {
public:
    virtual ~Event() = default;

    virtual EventType getEventType() const = 0;

    virtual std::string getName() const = 0;

    static EventType getStaticEventType() { return EventType::None; }

    friend std::ostream &operator<<(std::ostream &os, const Event &event) {
        os << event.getName();
        return os;
    }

public:
};




class EventDispatcher {
public:
    EventDispatcher(Event &event) : m_event(event) {}

    template<typename T, typename F>
    bool dispatchEvent(const F &callback) {
        if (m_event.getEventType() == T::getStaticEventType()) {
            callback(static_cast<T &>(m_event));
            return true;
        }
        return false;
    }

private:
    Event &m_event;

};

#endif
