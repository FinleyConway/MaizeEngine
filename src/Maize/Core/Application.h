#pragma once

#include <SFML/Graphics.hpp>

#include <memory>

int main();

namespace Maize {

	class Application
	{
	public:
		virtual ~Application() = default;

		bool Initialise(std::string_view title, uint32_t width, uint32_t height);
		void Quit();

	private:
		friend int ::main();

		bool Run();

	private:
		std::string m_Title = "MaizeEngine";
		sf::RenderWindow m_Window;
	};

} // Maize
