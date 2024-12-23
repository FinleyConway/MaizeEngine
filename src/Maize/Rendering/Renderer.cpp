#include "Maize/Rendering/Renderer.h"

#include "Maize/Core/Macros/Log.h"

namespace Maize
{
    Renderer::Renderer(sf::RenderWindow& window) : m_RenderWindow(window)
    {
        window.setView(sf::View({0, 0}, sf::Vector2f(window.getSize())));
    }

    const sf::View& Renderer::GetCurrentView() const
    {
        return m_RenderWindow.getView();
    }

    void Renderer::SetCurrentView(const sf::View& view) const
    {
        m_RenderWindow.setView(view);
    }

    void Renderer::BeginDrawing()
    {
        m_RenderWindow.clear();
        m_DrawCalls = 0;
    }

    void Renderer::Draw(std::span<const sf::Vertex> mesh, const sf::RenderStates& state)
    {
        // nothing to draw
        if (mesh.empty()) return;

        m_RenderWindow.draw(mesh.data(), mesh.size(), sf::PrimitiveType::Triangles, state);
        m_DrawCalls++;
    }

    void Renderer::EndDrawing()
    {
        m_RenderWindow.display();
    }

    uint32_t Renderer::GetDrawCalls() const
    {
        return m_DrawCalls;
    }

    sf::Vector2u Renderer::GetWindowSize() const
    {
        return m_RenderWindow.getSize();
    }
} // Maize
