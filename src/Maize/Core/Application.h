#pragma once

#include <SFML/Graphics.hpp>

#include <memory>

int main();

namespace Maize {

	class Application
	{
	public:
		Application(std::string_view title, uint32_t windowWidth, uint32_t windowHeight);
		virtual ~Application() = default;

		void Quit();

	private:
		friend int ::main();

		bool Run();

	private:
		std::string m_Title = "MaizeEngine";
		sf::RenderWindow m_Window;
	};

	// create engine from front end
	std::unique_ptr<Application> CreateApplication();

	#define MAIZE_ENGINE(type, name, width, height)					\
	std::unique_ptr<Maize::Application> Maize::CreateApplication()	\
	{																\
		return std::make_unique<type>(name, width, height);			\
	}

} // Maize
