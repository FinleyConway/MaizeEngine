#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

namespace Maize {

	struct Event;

	class EventHandler
	{
	public:
		explicit EventHandler(std::function<void(Event&)>&& callback);

		void Poll(sf::RenderWindow& window) const;

	private:
		std::function<void(Event&)> m_Callback;
	};

} // Maize