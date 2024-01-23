#ifndef EVENT_EVENT_H_
#define EVENT_EVENT_H_

#include <memory>
#include <string>
#include <Core/Log.h>

#define BIND_EVENT_FUNC(_Func) [this](auto&&... args) -> decltype(auto) { return this->_Func(std::forward<decltype(args)>(args)...); }
#define BIT(x) (1 << x)

enum class EventType
{
	None = 0,
	WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
	AppTick, AppUpdate, AppRender,
	KeyPressed, KeyReleased, KeyTyped,
	MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
};

enum EventCategory
{
	None = 0,
	EventCategoryApplication    = BIT(0),
	EventCategoryInput          = BIT(1),
	EventCategoryKeyboard       = BIT(2),
	EventCategoryMouse          = BIT(3),
	EventCategoryMouseButton    = BIT(4)
};

#define EVENT_CLASS_TYPE(type)	static EventType StaticType() { return type; }				\
								virtual EventType Type() const override { return StaticType(); }	\
								virtual const char* Name() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int CategoryFlags() const override { return category; }

class Event {
public:
	friend class EventDispatcher;
	virtual ~Event() = default;

	virtual EventType Type() const = 0;
	virtual const char* Name() const = 0;
	virtual int CategoryFlags() const = 0;
	virtual std::string ToString() const { return Name(); }

	bool IsInCategory(EventCategory _Category) const {
		return CategoryFlags() & _Category;
	}

	bool IsHandled() const { return m_IsHandled; }

private:
	bool m_IsHandled = false;
};

class EventDispatcher {
public:
    EventDispatcher(Event& _Event)
        : m_Event(_Event) {}

    template <class _EventCl, class _Func>
    bool Dispatch(const _Func& _EventCallbackFunc) {
		if (m_Event.Type() == _EventCl::StaticType()) {
			CORE_TRACE("%s\n", m_Event.ToString().c_str());
			m_Event.m_IsHandled |= _EventCallbackFunc(static_cast<_EventCl&>(m_Event));
			return true;
		}
		return false;
    }

private:
    Event& m_Event;
};

#endif // !EVENT_EVENT_H_
