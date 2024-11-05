#pragma once

#include <cstdint>

#define EVENT_CLASS_TYPE(type) \
static EventType GetStaticType() { return EventType::type; } \
EventType GetEventType() const override { return GetStaticType(); }

namespace Maize {

	enum class EventType
	{
		None,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	struct Event
	{
		bool handled = false;

		virtual ~Event() = default;
		virtual EventType GetEventType() const = 0;
	};

} // Maize