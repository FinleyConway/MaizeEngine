#pragma once

#include <flecs.h>

#include "Maize/Core/Macros/Assert.h"
#include "Maize/Core/Macros/Log.h"
#include "Maize/Rendering/Renderer.h"
#include "Maize/Scene/Components/Position.h"
#include "Maize/Scene/Components/Rendering/RenderingContext.h"
#include "Maize/Scene/Components/Rendering/SpriteRenderer.h"

namespace Maize
{
    class RenderingSystem
    {
    public:
        static void Render(flecs::entity entity, const Position& position, const SpriteRenderer& renderer)
        {
            const auto* ctx = entity.world().get<Internal::RenderingContext>();

            CORE_ASSERT(ctx != nullptr, "Rendering context has not been added!");
		    CORE_ASSERT(ctx->renderer != nullptr, "Rendering context was added but renderer wasn't!")

            RenderSprite(ctx->renderer, renderer, position);
        }

    private:
        static void RenderSprite(Renderer* renderer, const SpriteRenderer& spriteRenderer, const Position& position)
        {
            const auto& sprite = spriteRenderer.sprite;
            const auto pivot = sprite.GetPivot();
            const auto& texture = sprite.GetTexture().lock();
            const auto& vertices = sprite.GetVertices();

            sf::Transform transform = sf::Transform::Identity;
            transform.translate({ position.x - pivot.x, position.y - pivot.y }); // set position, based on pivot

            sf::RenderStates state;
            state.transform *= transform;
            state.texture = texture.get(); // want to place to use sf::Texture* rather than a weak_ptr

            renderer->Draw(vertices, state);
        }
    };

} // Maize::Internal
