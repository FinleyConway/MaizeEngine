#pragma once

#include "Maize/Event/Event.h"

namespace Maize {

	class EventDispatcher
	{
	public:
		explicit EventDispatcher(Event& event) : m_Event(event)
		{
		}

		template<typename TEvent, typename TFunction>
		bool Dispatch(TFunction&& func)
		{
			if (m_Event.GetEventType() == TEvent::GetStaticType())
			{
				m_Event.handled |= func(static_cast<TEvent&>(m_Event));

				return true;
			}

			return false;
		}

	private:
		Event& m_Event;
	};

} // Maize