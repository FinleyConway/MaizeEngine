#include "Maize/Core/Application.h"

namespace Maize {

	Application::Application(std::string_view title, uint32_t windowWidth, uint32_t windowHeight)
		: m_Title(title)
	{
		m_Window.create(sf::VideoMode(windowWidth, windowHeight), m_Title); // create window
		m_Window.setKeyRepeatEnabled(false); // disable text editor hold key like functionality
		m_Window.setVerticalSyncEnabled(true); // turn on v-sync by default
	}

	void Application::Quit()
	{
		m_Window.close();
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