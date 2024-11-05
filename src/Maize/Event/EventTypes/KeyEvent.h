#pragma once

#include "Maize/Event/Event.h"
#include "Maize/Core/KeyCodes.h"

namespace Maize {

	class KeyEvent : public Event
	{
	public:
		KeyCode GetKeyCode() const
		{
			return m_KeyCode;
		}

	protected:
		explicit KeyEvent(KeyCode keycode) : m_KeyCode(keycode)
		{
		}

		KeyCode m_KeyCode;
	};

	class KeyPressedEvent final : public KeyEvent
	{
	public:
		explicit KeyPressedEvent(KeyCode keycode) : KeyEvent(keycode)
		{
		}

		EVENT_CLASS_TYPE(KeyPressed)
	};

	class KeyReleasedEvent final : public KeyEvent
	{
	public:
		explicit KeyReleasedEvent(KeyCode keycode) : KeyEvent(keycode)
		{
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

} // Maize