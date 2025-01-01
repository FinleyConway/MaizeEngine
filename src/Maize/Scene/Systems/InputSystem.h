#pragma once

#include <SFML/Graphics.hpp>
#include <flecs.h>

namespace Maize::Internal
{
    /**
     * Handles the Input singleton that provides state for when input happens.
     */
    class InputSystem
    {
    public:
        /**
         * Creates the input singleton when creating an instance.
         * @param world The ecs world.
         * @param window The window of the application.
         */
        explicit InputSystem(const flecs::world& world, const sf::RenderWindow& window);

        /**
         * Handles all the incoming events.
         * @param event The event incoming.
         */
        void OnEvent(const std::optional<sf::Event>& event) const;

    private:
        void OnKeyPressed(const sf::Event::KeyPressed& event) const;

        void OnKeyReleased(const sf::Event::KeyReleased& event) const;

        void OnMouseMoved(const sf::Event::MouseMoved& event) const;

        void OnMouseButtonPressed(const sf::Event::MouseButtonPressed& event) const;

        void OnMouseButtonReleased(const sf::Event::MouseButtonReleased& event) const;

    private:
        const flecs::world& m_World;
        const sf::RenderWindow& m_Window;
    };
} // Maize::Internal
