#ifndef AUTM_EVENT_H
#define AUTM_EVENT_H

#include "autmpch.h"

#define AUTM_BIND_EVENT(x) std::bind(&x, this, std::placeholders::_1)

enum class EventType {
    None = 0,
    MouseButtonPressed = 1,
    MouseButtonReleased = 2,
    MouseMoved = 3,
    MouseScrolled = 4,
    KeyPressed = 5,
    KeyReleased = 6,
    WindowResized,
    WindowClosed
};

enum EventCategory {
    None = 0,
    EventCategoryApplication = 0x01,
    EventCategoryInput = 0x02,
    EventCategoryKeyboard = 0x04,
    EventCategoryMouse = 0x08,
    EventCategoryMouseButton = 0x10,

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

    EventResult getEventResult() const { return m_eventResult; }

    void setEventResult(EventResult result) { m_eventResult = result; }

    virtual int getCategory() const { return EventCategory::None; };

    bool isInCategory(EventCategory category) { return getCategory() & category; }

    static EventType getStaticEventType() { return EventType::None; }

    friend std::ostream& operator<<(std::ostream& os, const Event& event) {
        os << event.getName();
        return os;
    }

private:
    EventResult m_eventResult = EventResult::Pass;

    friend class EventDispatcher;
};


class EventDispatcher {
public:
    explicit EventDispatcher(Event& event) : m_event(event) {}

    template<typename T, typename F>
    bool dispatchEvent(const F& callback) {
        if (m_event.getEventType() == T::getStaticEventType()) {
            m_event.m_eventResult = callback(static_cast<T&>(m_event));
            return true;
        }
        return false;
    }

private:
    Event& m_event;

};

#endif
