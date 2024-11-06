#pragma once

#include <SFML/Graphics.hpp>

#include <memory>

#include "Maize/Rendering/Renderer.h"
#include "Maize/Rendering/Sprite.h"

namespace Maize {

	struct Event;
	class WindowCloseEvent;

	class Application
	{
	public:
		virtual ~Application() = default;

		bool Initialise(std::string_view title, uint32_t width, uint32_t height);
		bool Run();
		void Quit();

	private:
		void OnEvent(Event& event);
		bool OnWindowClose(const WindowCloseEvent&);

	private:
		std::string m_Title = "MaizeEngine";
		sf::RenderWindow m_Window;
		Renderer m_Renderer;

		std::shared_ptr<sf::Texture> m_Texture;
		Sprite m_Sprite;
	};

} // Maize
