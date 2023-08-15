#ifndef AUTM_KEYEVENTS_H
#define AUTM_KEYEVENTS_H

#include "Event.h"

class KeyEvent : public Event {
public:
    explicit KeyEvent(int keycode, int mods) : m_keycode(keycode), m_mods(mods) {}

    inline int get_keycodes() const { return m_keycode; }

    inline int get_mods() const { return m_mods; }

    int get_category() const override {
        return EventCategoryKeyboard | EventCategoryInput;
    }

protected:
    int m_keycode, m_mods;
};


class KeyPressedEvent : public KeyEvent {
public:
    explicit KeyPressedEvent(int keyCode, int mods, bool repeat = false) : KeyEvent(keyCode, mods), m_repeat(repeat) {}

    virtual EventType get_event_type() const override { return get_static_event_type(); }

    virtual std::string get_name() const { return "KeyPressedEvent"; }

    bool is_repeating() const { return m_repeat; }

    static EventType get_static_event_type() { return EventType::KeyPressed; }

private:
    bool m_repeat;
};

class KeyReleasedEvent : public KeyEvent {
public:
    explicit KeyReleasedEvent(int keycode, int mods) : KeyEvent(keycode, mods) {}

    virtual EventType get_event_type() const override { return get_static_event_type(); }

    virtual std::string get_name() const { return "KeyReleasedEvent"; }

    static EventType get_static_event_type() { return EventType::KeyReleased; }
};

#endif
