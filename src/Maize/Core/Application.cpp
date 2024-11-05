#include "Maize/Core/Application.h"
#include "Maize/Core/Macros/Log.h"

namespace Maize {

	void Application::Quit()
	{
		m_Window.close();
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

		while (m_Window.isOpen())
		{
			for (auto event = sf::Event(); m_Window.pollEvent(event); )
			{
				if (event.type == sf::Event::Closed)
				{
					m_Window.close();
				}
			}

			const float deltaTime = clock.restart().asSeconds();


		}

		return true;
	}

} // Maize