#include "Maize/Rendering/Renderer.h"

#include "Maize/Core/Macros/Assert.h"
#include "Maize/Core/Macros/Log.h"

namespace Maize {

	void Renderer::Initialise(sf::RenderWindow& window)
	{
		m_RenderWindow = &window;
		m_RenderWindow->setView(sf::View({ 0, 0 }, sf::Vector2f(window.getSize())));
	}

	const sf::View& Renderer::GetCurrentView() const
	{
		CORE_ASSERT(m_RenderWindow != nullptr, "RenderWindow is null!")

		return m_RenderWindow->getView();
	}

	void Renderer::SetCurrentView(const sf::View& view) const
	{
		CORE_ASSERT(m_RenderWindow != nullptr, "RenderWindow is null!")

		m_RenderWindow->setView(view);
	}

	void Renderer::BeginDrawing()
	{
		CORE_ASSERT(m_RenderWindow != nullptr, "RenderWindow is null!")

		m_RenderWindow->clear();
		m_DrawCalls = 0;
	}

	void Renderer::Draw(std::span<const sf::Vertex> mesh, const sf::RenderStates& state)
	{
		CORE_ASSERT(m_RenderWindow != nullptr, "RenderWindow is null!")

		// nothing to draw
		if (mesh.empty()) return;

		m_RenderWindow->draw(mesh.data(), mesh.size(), sf::Triangles, state);
		m_DrawCalls++;
	}

	void Renderer::EndDrawing()
	{
		CORE_ASSERT(m_RenderWindow != nullptr, "RenderWindow is null!")

		m_RenderWindow->display();
	}

	uint32_t Renderer::GetDrawCalls() const
	{
		return m_DrawCalls;
	}

	sf::Vector2u Renderer::GetWindowSize() const
	{
		CORE_ASSERT(m_RenderWindow != nullptr, "RenderWindow is null!")

		return m_RenderWindow->getSize();
	}

} // Maize