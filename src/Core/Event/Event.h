#ifndef AUTM_EVENT_H
#define AUTM_EVENT_H

#include "autmpch.h"

#define BIND_EVENT_FUNCTION(x) std::bind(&x, this, std::placeholders::_1)

enum class EventType {
    None = 0,
    MouseButtonPressed = 1,
    MouseButtonReleased = 2,
    MouseMoved = 3,
    MouseScrolled = 4,
    KeyPressed = 5,
    KeyReleased = 6,
    WindowResizedEvent
};

enum class EventResult {
    Consume, // Means the event handler succeeded and the next layer should not receive it.
    Pass, // Means the event handler does nothing and passes it along to the next layer.
    Fail // Means something went wrong in the event handler and the next layer should not receive it.
};

class Event {
public:
    virtual ~Event() = default;

    virtual EventType getEventType() const = 0;

    virtual std::string getName() const = 0;

    // TODO: Implement EventResults
//    void setResult(EventResult eventResult) { m_eventResult = eventResult; }

//    EventResult getResult() const { return m_eventResult; }

    static EventType getStaticEventType() { return EventType::None; }

    friend std::ostream& operator<<(std::ostream& os, const Event& event) {
        os << event.getName();
        return os;
    }

private:
//    EventResult m_eventResult;
};


class EventDispatcher {
public:
    EventDispatcher(Event& event) : m_event(event) {}

    template<typename T, typename F>
    bool dispatchEvent(const F& callback) {
        if (m_event.getEventType() == T::getStaticEventType()) {
            // TODO: Set event's "ActionResult" to the result of the callback.
//            m_event.setResult(callback(static_cast<T&>(m_event)));
            callback(static_cast<T&>(m_event));
//            m_event.setResult(EventResult::Consume);
            return true;
        }
        return false;
    }

private:
    Event& m_event;

};

#endif
