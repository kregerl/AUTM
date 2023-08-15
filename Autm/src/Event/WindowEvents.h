#ifndef AUTM_WINDOWEVENTS_H
#define AUTM_WINDOWEVENTS_H

class WindowResizedEvent : public Event {
public:
    WindowResizedEvent(int width, int height) : m_width(width), m_height(height) {}

    virtual EventType get_event_type() const override { return get_static_event_type(); };

    virtual std::string get_name() const { return "WindowResizedEvent"; }

    static EventType get_static_event_type() { return EventType::WindowResized; }

    int get_width() const { return m_width; }

    int get_height() const { return m_height; }

    glm::vec2 get_size() const { return {m_width, m_height}; }

protected:
    int m_width, m_height;
};

class WindowClosedEvent : public Event {
public:
    WindowClosedEvent() = default;

    ~WindowClosedEvent() override = default;

    virtual EventType get_event_type() const override { return get_static_event_type(); }

    virtual std::string get_name() const override { return "WindowClosedEvent"; }

    static EventType get_static_event_type() { return EventType::WindowClosed; }
};

#endif //AUTM_WINDOWEVENTS_H
