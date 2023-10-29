#ifndef AUTM_EVENT_H
#define AUTM_EVENT_H

#include "autmpch.h"

#define AUTM_BIND(x) std::bind(&x, this, std::placeholders::_1)

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
    Consume, // Means the event handler succeeded and the event was consumed.
    Pass, // Means the event handler will pass the event to the next layer.
    Deny // Means the event should not be passed to the next layer.
};

class Event {
public:
    virtual ~Event() = default;

    virtual EventType get_event_type() const = 0;

    virtual std::string get_name() const = 0;

    EventResult get_event_result() const { return m_event_result; }

    void set_event_result(EventResult result) { m_event_result = result; }

    virtual int get_category() const { return EventCategory::None; };

    bool is_in_category(EventCategory category) { return get_category() & category; }

    static EventType get_static_event_type() { return EventType::None; }

    friend std::ostream& operator<<(std::ostream& os, const Event& event) {
        os << event.get_name();
        return os;
    }

private:
    EventResult m_event_result = EventResult::Pass;

    friend class EventDispatcher;
};


class EventDispatcher {
public:
    explicit EventDispatcher(Event& event) : m_event(event) {}

    template<typename T, typename F>
    bool dispatch_event(const F& callback) {
        if (m_event.get_event_type() == T::get_static_event_type()) {
            m_event.m_event_result = callback(static_cast<T&>(m_event));
            return true;
        }
        return false;
    }

private:
    Event& m_event;

};

#endif
