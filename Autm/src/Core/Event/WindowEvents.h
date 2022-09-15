#ifndef AUTM_WINDOWEVENTS_H
#define AUTM_WINDOWEVENTS_H

class WindowResizedEvent : public Event {
public:
    explicit WindowResizedEvent(int width, int height) : m_width(width), m_height(height) {}

    virtual EventType getEventType() const override { return getStaticEventType(); };

    virtual std::string getName() const { return "WindowResizedEvent"; }

    static EventType getStaticEventType() { return EventType::WindowResizedEvent; }

    int getWidth() const { return m_width; }

    int getHeight() const { return m_height; }

    glm::vec2 getSize() const { return {m_width, m_height}; }

protected:
    int m_width, m_height;
};

#endif //AUTM_WINDOWEVENTS_H
