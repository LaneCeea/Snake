#ifndef EVENT_KEYEVENT_H_
#define EVENT_KEYEVENT_H_

#include "Event.h"

#include <Core/Log.h>
#include <Core/KeyCode.h>

class KeyEvent : public Event {
public:
    KeyEvent(int key, int scancode, int action, int mods) :
        m_Key(key), m_Scancode(scancode), m_Action(action), m_Mods(mods) {}

    constexpr int Key() const       { return m_Key; }
    constexpr int Scancode() const  { return m_Scancode; }
    constexpr int Action() const    { return m_Action; }
    constexpr int Mods() const      { return m_Mods; }
    
    void Trace() const override {
        const std::string_view _KeyName = Key::KeyCodeToStringView(m_Key);
        const std::string_view _ActionName = (
            m_Action == 0 ? "RELEASE" : 
            m_Action == 1 ? "PRESS" : "REPEAT"
            );
        CORE_TRACE("%s: %s, %s\n", Name(), _KeyName.data(), _ActionName.data());
    }

    EVENT_CLASS_TYPE(EventType::Key)
    EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKeyboard)

private:
    int m_Key, m_Scancode, m_Action, m_Mods;
};

#endif // !EVENT_KEYEVENT_H_
