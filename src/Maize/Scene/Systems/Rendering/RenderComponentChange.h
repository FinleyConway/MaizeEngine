#pragma once

#include <flecs.h>

#include "Maize/Scene/Components/Position.h"
#include "Maize/Scene/Components/Rendering/SpriteRenderer.h"

namespace Maize::Internal
{
    struct RenderingContext;

    class RenderComponentChange
    {
    public:
        /**
         * Handles the removal of the sprite renderer component, removing it from the spatial index.
         * @param entity The entity.
         */
        static void OnSpriteRendererRemove(flecs::entity entity, const SpriteRenderer&);

        /**
         * Adds the entity to the spatial index when the entity components were deferred.
         * @param entity The entity.
         * @param position The position component.
         * @param spriteRenderer The sprite renderer component.
         */
        static void HandleSpriteRendererDefer(flecs::entity entity, const Position& position,
            const SpriteRenderer& spriteRenderer);
    };
} // Maize::Internal
