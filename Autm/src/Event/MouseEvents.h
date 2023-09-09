#ifndef AUTM_MOUSEEVENTS_H
#define AUTM_MOUSEEVENTS_H

#include <glm/glm.hpp>
#include "Event.h"

class MouseButtonEvent : public Event {
public:
    explicit MouseButtonEvent(int mouse_button, int mods, float x_pos, float y_pos) : m_mouse_button(mouse_button),
                                                                                      m_mods(mods), m_x_pos(x_pos),
                                                                                      m_y_pos(y_pos) {}

    inline int getMouseButton() const { return m_mouse_button; }

    inline glm::vec2 getMousePos() const { return {m_x_pos, m_y_pos}; }

    inline float getMouseX() const { return m_x_pos; }

    inline float getMouseY() const { return m_y_pos; }

    int get_category() const override {
        return EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton;
    }

protected:
    int m_mouse_button, m_mods;
    float m_x_pos, m_y_pos;
};


class MouseButtonPressedEvent : public MouseButtonEvent {
public:
    explicit MouseButtonPressedEvent(int mouseButton, int mods, float xPos, float yPos) : MouseButtonEvent(
            mouseButton, mods, xPos, yPos) {}

    virtual EventType get_event_type() const override { return get_static_event_type(); };

    virtual std::string get_name() const { return "MouseButtonPressed"; }

    static EventType get_static_event_type() { return EventType::MouseButtonPressed; }
};


class MouseButtonReleasedEvent : public MouseButtonEvent {
public:
    explicit MouseButtonReleasedEvent(int mouseButton, int mods, float xPos, float yPos) : MouseButtonEvent(
            mouseButton, mods, xPos, yPos) {}

    virtual EventType get_event_type() const override { return get_static_event_type(); };

    virtual std::string get_name() const { return "MouseButtonReleased"; }

    static EventType get_static_event_type() { return EventType::MouseButtonReleased; }
};

class MouseScrolledEvent : public Event {
public:
    MouseScrolledEvent(float x_offset, float y_offset, float x_pos, float y_pos) : m_x_offset(x_offset),
                                                                                   m_y_offset(y_offset), m_x_pos(x_pos),
                                                                                   m_y_pos(y_pos) {}

    MouseScrolledEvent(float x_offset, float y_offset) : m_x_offset(x_offset), m_y_offset(y_offset) {}

    glm::vec2 get_mouse_offset() const { return {m_x_offset, m_y_offset}; }

    float get_mouse_offset_x() const { return m_x_offset; }

    float get_mouse_offset_y() const { return m_y_offset; }

    glm::vec2 get_mouse_pos() const { return {m_x_pos, m_y_pos}; }

    virtual EventType get_event_type() const override { return get_static_event_type(); }

    virtual std::string get_name() const { return "MouseScrolled"; }

    int get_category() const override {
        return EventCategoryMouse | EventCategoryInput;
    }

    static EventType get_static_event_type() { return EventType::MouseScrolled; }

private:
    float m_x_offset, m_y_offset, m_x_pos, m_y_pos;

};

class MouseMovedEvent : public Event {
public:
    MouseMovedEvent(float x, float y) : m_x_pos(x), m_y_pos(y) {}

    float get_x() const { return m_x_pos; }

    float get_y() const { return m_y_pos; }

    EventType get_event_type() const override { return get_static_event_type(); }

    std::string get_name() const override { return "MouseMoved"; }

    int get_category() const override {
        return EventCategoryMouse | EventCategoryInput;
    }

    static EventType get_static_event_type() { return EventType::MouseMoved; }

private:
    float m_x_pos, m_y_pos;
};

#endif
