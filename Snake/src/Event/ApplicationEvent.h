#ifndef EVENT_APPLICATIONEVENT_H_
#define EVENT_APPLICATIONEVENT_H_

#include "Event.h"

#include <cstdint>
#include <sstream>

class WindowCloseEvent : public Event {
public:
    WindowCloseEvent() = default;

    EVENT_CLASS_TYPE(EventType::WindowClose)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class WindowResizeEvent : public Event {
public:
	WindowResizeEvent(std::uint32_t _Width, std::uint32_t _Height)
		: m_Width(_Width), m_Height(_Height) {}

    std::uint32_t GetWidth() const { return m_Width; }
    std::uint32_t GetHeight() const { return m_Height; }

	std::string ToString() const override {
		std::stringstream ss;
		ss << Name() << ": " << m_Width << ", " << m_Height;
		return ss.str();
	}

    EVENT_CLASS_TYPE(EventType::WindowResize)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)

private:
    std::uint32_t m_Width, m_Height;
};

#endif // !EVENT_APPLICATIONEVENT_H_
