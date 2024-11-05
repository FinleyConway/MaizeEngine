#pragma once

#include "Maize/Event/Event.h"

namespace Maize {

	class WindowCloseEvent final : public Event
	{
	public:
		WindowCloseEvent() = default;

		EVENT_CLASS_TYPE(WindowClose)
	};

	class WindowResizeEvent final : public Event
	{
	public:
		WindowResizeEvent(uint32_t width, uint32_t height) : m_Width(width), m_Height(height)
		{
		}

		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }

		EVENT_CLASS_TYPE(WindowResize)

	private:
		uint32_t m_Width;
		uint32_t m_Height;
	};

} // Maize