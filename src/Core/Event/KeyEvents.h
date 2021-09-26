#ifndef AUTM_KEYEVENTS_H
#define AUTM_KEYEVENTS_H

#include "Event.h"

class KeyEvent : public Event {
public:
    explicit KeyEvent(int keyCode, int mods) : m_keyCode(keyCode), m_mods(mods) {}

    inline int getKeyCode() const { return m_keyCode; }

    inline int getMods() const { return m_mods; }

protected:
    int m_keyCode, m_mods;
};


class KeyPressedEvent : public KeyEvent {
public:
    explicit KeyPressedEvent(int keyCode, int mods, bool repeat = false) : KeyEvent(keyCode, mods), m_repeat(repeat) {}

    virtual EventType getEventType() const override { return getStaticEventType(); }

    virtual std::string getName() const { return "KeyPressedEvent"; }

    bool getRepeat() const { return m_repeat; }

    static EventType getStaticEventType() { return EventType::KeyPressed; }

private:
    bool m_repeat;
};

class KeyReleasedEvent : public KeyEvent {
public:
    explicit KeyReleasedEvent(int keyCode, int mods) : KeyEvent(keyCode, mods) {}

    virtual EventType getEventType() const override { return getStaticEventType(); }

    virtual std::string getName() const { return "KeyReleasedEvent"; }

    static EventType getStaticEventType() { return EventType::KeyReleased; }
};

#endif
