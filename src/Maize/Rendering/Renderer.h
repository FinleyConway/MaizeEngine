#pragma once

#include <SFML/Graphics.hpp>

#include <span>

namespace Maize
{
    class Renderer
    {
    public:
        explicit Renderer(sf::RenderWindow& window);

        const sf::View& GetCurrentView() const;

        void SetCurrentView(const sf::View& view) const;

        void BeginDrawing();

        void Draw(std::span<const sf::Vertex> mesh, const sf::RenderStates& state);

        void EndDrawing();

        uint32_t GetDrawCalls() const;

        sf::Vector2u GetWindowSize() const;

    private:
        sf::RenderWindow& m_RenderWindow;
        uint32_t m_DrawCalls = 0;
    };
} // Maize
