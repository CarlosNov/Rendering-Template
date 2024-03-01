#pragma once

#include "Core/Core.h"

namespace Core
{
#define EVENT_CLASS_TYPE(eventType)  static EventType GetStaticType() { return EventType::##eventType; } \
									 virtual EventType GetEventType() const override { return GetStaticType(); } \
									 virtual const char* GetEventName() const override { return #eventType; }

#define EVENT_CLASS_CATEGORY(eventCategory)  virtual int GetEventCategory() const override { return eventCategory; }

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppRender, AppUpdate,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryWindow =		DEFINE_BIT(0),
		EventCategoryApplication =	DEFINE_BIT(1),
		EventCategoryInput =        DEFINE_BIT(2),
		EventCategoryKeyboard =		DEFINE_BIT(3),
		EventCategoryMouse =		DEFINE_BIT(4),
		EventCategoryMouseButton =	DEFINE_BIT(5)
	};

	class Event
	{
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetEventName() const = 0;
		virtual int GetEventCategory() const = 0;
		virtual std::string ToString() const { return "Event(eventName: " + std::string(GetEventName()) + ", eventCategory: " + std::to_string(GetEventCategory()) +")"; }

		bool IsInCategory(EventCategory eventCategory)
		{
			return GetEventCategory() & eventCategory;
		}

		bool IsHandled() { return m_Handled; }

		std::ostream& operator<<(std::ostream& os)
		{
			return os << ToString();
		}

	protected:
		bool m_Handled = false;
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event) : m_Event(event) {}

		template<typename T, typename F>
		bool Dispatch(const F& function)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = function(*(T*)&m_Event);
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};
}