#pragma once

#include <SFML/Graphics.hpp>

namespace Maize::Internal
{
    class Renderer
    {
    public:
        explicit Renderer(sf::RenderWindow& window);

        /**
         * Get the current camera view being used on the current render target.
         * @return The camera view.
         */
        const sf::View& GetCurrentView() const;

        /**
         * Set the current camera view to be used on the current render target
         * @param view The camera view.
         */
        void SetCurrentView(const sf::View& view) const;

        /**
         * Start the drawing process.
         */
        void BeginDrawing();

        /**
         * Draw a mesh object.
         * @param mesh An array of vertices defining the shape of the mesh.
         * @param state Defines the state on how the mesh gets drawn.
         */
        void Draw(std::span<const sf::Vertex> mesh, const sf::RenderStates& state);

        /**
         * End the drawing process.
         */
        void EndDrawing();

        /**
         * Get the amount of objects being drawn currently.
         * @return The amount.
         */
        uint32_t GetDrawCalls() const;

        /**
         * Get the size of the window.
         * @return The size of the window.
         */
        sf::Vector2u GetWindowSize() const;

        /**
         * Get the rendering window.
         * @return The window.
         */
        const sf::RenderWindow& GetWindow() const;

    private:
        sf::RenderWindow& m_RenderWindow;
        uint32_t m_DrawCalls = 0;
    };
} // Maize::Internal
