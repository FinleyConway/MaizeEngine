#include "Maize/Core/Application.h"

#include "Maize/Core/Macros/Log.h"
#include "Maize/Event/EventHandler.h"
#include "Maize/Event/EventDispatcher.h"
#include "Maize/Event/EventTypes/WindowEvent.h"

namespace Maize {

	void Application::Quit()
	{
		m_Window.close();
	}

	void Application::OnEvent(Event& event)
	{
		auto dispatcher = EventDispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
	}

	bool Application::OnWindowClose(const WindowCloseEvent&)
	{
		m_Window.close();

		return false;
	}

	bool Application::Initialise(std::string_view title, uint32_t width, uint32_t height)
	{
		Log::Initialise();

		// make sure that the size of the screen is not a stupid size
		if (!(width > 0 && height > 0))
		{
			CORE_LOG_WARN("Screen size must be larger then 0 in both axes!");
			return false;
		}

		m_Title = title;

		m_Window.create(sf::VideoMode(width, height), m_Title); // create window
		m_Window.setKeyRepeatEnabled(false); // disable text editor hold key like functionality
		m_Window.setVerticalSyncEnabled(true); // turn on v-sync by default

		return true;
	}

	bool Application::Run()
	{
		sf::Clock clock;
		const auto pollEvent = EventHandler(std::bind(&Application::OnEvent, this, std::placeholders::_1));

		while (m_Window.isOpen())
		{
			pollEvent.Poll(m_Window);

			const float deltaTime = clock.restart().asSeconds();
		}

		return true;
	}

} // Maize