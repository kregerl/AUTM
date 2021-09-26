#ifndef AUTM_MOUSEEVENTS_H
#define AUTM_MOUSEEVENTS_H

#include <glm/glm.hpp>
#include "Event.h"

class MouseButtonEvent : public Event {
public:
    explicit MouseButtonEvent(int mouseButton, int mods, double xPos, double yPos) : m_mouseButton(mouseButton),
                                                                                     m_mods(mods), m_xPos(xPos),
                                                                                     m_yPos(yPos) {}

    inline int getMouseButton() const { return m_mouseButton; }

    inline glm::vec2 getMousePos() const { return {m_xPos, m_yPos}; }

    inline double getMouseX() const { return m_xPos; }

    inline double getMouseY() const { return m_yPos; }

protected:
    int m_mouseButton, m_mods;
    double m_xPos, m_yPos;
};


class MouseButtonPressedEvent : public MouseButtonEvent {
public:
    explicit MouseButtonPressedEvent(int mouseButton, int mods, double xPos, double yPos) : MouseButtonEvent(
            mouseButton, mods, xPos, yPos) {}

    virtual EventType getEventType() const override { return getStaticEventType(); };

    virtual std::string getName() const { return "MouseButtonPressedEvent"; }

    static EventType getStaticEventType() { return EventType::MouseButtonPressed; }
};


class MouseButtonReleasedEvent : public MouseButtonEvent {
public:
    explicit MouseButtonReleasedEvent(int mouseButton, int mods, double xPos, double yPos) : MouseButtonEvent(
            mouseButton, mods, xPos, yPos) {}

    virtual EventType getEventType() const override { return getStaticEventType(); };

    virtual std::string getName() const { return "MouseButtonReleasedEvent"; }

    static EventType getStaticEventType() { return EventType::MouseButtonReleased; }
};

class MouseScrolledEvent : public Event {
public:
    explicit MouseScrolledEvent(double xOffset, double yOffset) : m_xOffset(xOffset), m_yOffset(yOffset) {}

    glm::vec2 getMouseOffset() const { return {m_xOffset, m_yOffset}; }

    double getMouseOffsetX() const { return m_xOffset; }

    double getMouseOffsetY() const { return m_yOffset; }

    virtual EventType getEventType() const override { return getStaticEventType(); }

    virtual std::string getName() const { return "MouseScrolledEvent"; }

    static EventType getStaticEventType() { return EventType::MouseScrolled; }

private:
    double m_xOffset, m_yOffset;

};

#endif
