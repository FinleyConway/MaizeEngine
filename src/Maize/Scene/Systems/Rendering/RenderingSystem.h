#pragma once

#include <flecs.h>
#include <SFML/Graphics/View.hpp>

#include "Maize/Scene/Components/Position.h"

namespace Maize
{
    struct Camera;
    struct SpriteRenderer;

    namespace Internal
    {
        class Renderer;

        class RenderingSystem
        {
        public:
            static void UpdateSpriteRendererPosition(flecs::entity entity, const Position& position,
                const SpriteRenderer& spriteRenderer);

            static void Render(flecs::entity entity, const Position& position, Camera& camera);

        private:
            static sf::View SetupCurrentCamera(const Renderer* renderer, const Position& position, Camera& camera);

            static void RenderSprite(Renderer* renderer, const SpriteRenderer& spriteRenderer, const Position& position);
        };
    } // Internal
} // Maize
