#ifndef AUTM_MOUSEEVENTS_H
#define AUTM_MOUSEEVENTS_H

#include <glm/glm.hpp>
#include "Event.h"

class MouseButtonEvent : public Event {
public:
    explicit MouseButtonEvent(int mouseButton, int mods, float xPos, float yPos) : m_mouseButton(mouseButton),
                                                                                   m_mods(mods), m_xPos(xPos),
                                                                                   m_yPos(yPos) {}

    inline int getMouseButton() const { return m_mouseButton; }

    inline glm::vec2 getMousePos() const { return {m_xPos, m_yPos}; }

    inline float getMouseX() const { return m_xPos; }

    inline float getMouseY() const { return m_yPos; }

    int getCategory() const override {
        return EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton;
    }

protected:
    int m_mouseButton, m_mods;
    float m_xPos, m_yPos;
};


class MouseButtonPressedEvent : public MouseButtonEvent {
public:
    explicit MouseButtonPressedEvent(int mouseButton, int mods, float xPos, float yPos) : MouseButtonEvent(
            mouseButton, mods, xPos, yPos) {}

    virtual EventType getEventType() const override { return getStaticEventType(); };

    virtual std::string getName() const { return "MouseButtonPressed"; }

    static EventType getStaticEventType() { return EventType::MouseButtonPressed; }
};


class MouseButtonReleasedEvent : public MouseButtonEvent {
public:
    explicit MouseButtonReleasedEvent(int mouseButton, int mods, float xPos, float yPos) : MouseButtonEvent(
            mouseButton, mods, xPos, yPos) {}

    virtual EventType getEventType() const override { return getStaticEventType(); };

    virtual std::string getName() const { return "MouseButtonReleased"; }

    static EventType getStaticEventType() { return EventType::MouseButtonReleased; }
};

class MouseScrolledEvent : public Event {
public:
    MouseScrolledEvent(float xOffset, float yOffset, float xPos, float yPos) : m_xOffset(xOffset),
                                                                               m_yOffset(yOffset), m_xPos(xPos),
                                                                               m_yPos(yPos) {}

    MouseScrolledEvent(float xOffset, float yOffset) : m_xOffset(xOffset), m_yOffset(yOffset) {}

    glm::vec2 getMouseOffset() const { return {m_xOffset, m_yOffset}; }

    float getMouseOffsetX() const { return m_xOffset; }

    float getMouseOffsetY() const { return m_yOffset; }

    glm::vec2 getMousePos() const { return {m_xPos, m_yPos}; }

    virtual EventType getEventType() const override { return getStaticEventType(); }

    virtual std::string getName() const { return "MouseScrolled"; }

    int getCategory() const override {
        return EventCategoryMouse | EventCategoryInput;
    }

    static EventType getStaticEventType() { return EventType::MouseScrolled; }

private:
    float m_xOffset, m_yOffset, m_xPos, m_yPos;

};

class MouseMovedEvent : public Event {
public:
    MouseMovedEvent(float x, float y) : m_xPos(x), m_yPos(y) {}

    float getX() const { return m_xPos; }

    float getY() const { return m_yPos; }

    EventType getEventType() const override { return getStaticEventType(); }

    std::string getName() const override { return "MouseMoved"; }

    int getCategory() const override {
        return EventCategoryMouse | EventCategoryInput;
    }

    static EventType getStaticEventType() { return EventType::MouseMoved; }

private:
    float m_xPos, m_yPos;
};

#endif
