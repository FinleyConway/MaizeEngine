#pragma once

#include <flecs.h>
#include <SFML/Graphics/View.hpp>

#include "Maize/Scene/Components/Position.h"
#include "Maize/Scene/Components/Rendering/Camera.h"
#include "Maize/Scene/Components/Rendering/RenderingContext.h"
#include "Maize/Scene/Components/Rendering/SpriteRenderer.h"
#include "Maize/Scene/Components/Rendering/MeshRenderer.h"
#include "Maize/Scene/Components/Rendering/GridRenderer.h"
#include "Maize/Rendering/Renderer.h"

namespace Maize::Internal
{
    class RenderingSystem
    {
    public:
        static void Render(flecs::entity entity, const Position& position, Camera& camera);

    private:
        static void RenderEntities(const std::vector<flecs::entity_t>& entities, flecs::world world, Renderer* renderer);

        static sf::View SetupCurrentCamera(const Renderer* renderer, const Position& position, Camera& camera);

        static sf::Transform CreateTransform(const Position& position, Vec2f pivot = Vec2f());

        static sf::RenderStates CreateRenderState(const sf::Transform& transform, const std::shared_ptr<sf::Texture>& texture);

        static void RenderSprite(Renderer* renderer, const SpriteRenderer& spriteRenderer, const Position& position);

        static void RenderMesh(Renderer* renderer, const MeshRenderer& meshRenderer, const Position& position);

        static void RenderGrid(Renderer* renderer, const GridRenderer& gridRenderer, const Position& position);
    };
} // Maize::Internal

