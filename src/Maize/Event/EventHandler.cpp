#include "Maize/Event/EventHandler.h"
#include "Maize/Event/EventTypes/WindowEvent.h"
#include "Maize/Event/EventTypes/MouseEvent.h"
#include "Maize/Event/EventTypes/KeyEvent.h"

namespace Maize {

	EventHandler::EventHandler(std::function<void(Event&)>&& callback) : m_Callback(std::move(callback))
	{
	}

	void EventHandler::Poll(sf::RenderWindow& window) const
	{
		for (auto e = sf::Event(); window.pollEvent(e); )
		{
			switch (e.type)
			{
				case sf::Event::Closed:
				{
					WindowCloseEvent event;
					m_Callback(event);
					break;
				}
				case sf::Event::Resized:
				{
					auto event = WindowResizeEvent(e.size.width, e.size.height);
					m_Callback(event);
					break;
				}
				case sf::Event::KeyPressed:
				{
					auto event = KeyPressedEvent(static_cast<KeyCode>(e.key.code));
					m_Callback(event);
					break;
				}
				case sf::Event::KeyReleased:
				{
					auto event = KeyReleasedEvent(static_cast<KeyCode>(e.key.code));
					m_Callback(event);
					break;
				}
				case sf::Event::MouseButtonPressed:
				{
					auto event = MouseButtonPressedEvent(static_cast<MouseCode>(e.mouseButton.button));
					m_Callback(event);
					break;
				}
				case sf::Event::MouseButtonReleased:
				{
					auto event = MouseButtonReleasedEvent(static_cast<MouseCode>(e.mouseButton.button));
					m_Callback(event);
					break;
				}
				case sf::Event::MouseMoved:
				{
					auto event = MouseMovedEvent(e.mouseMove.x, e.mouseMove.y);
					m_Callback(event);
					break;
				}
				case sf::Event::MouseWheelMoved:
				{
					auto event = MouseScrolledEvent(0, e.mouseWheel.delta);
					m_Callback(event);
					break;
				}

				default: break;
			}
		}
	}

} // Maize