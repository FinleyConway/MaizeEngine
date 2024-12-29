#pragma once

#include <flecs.h>

#include "Maize/Scene/Components/Position.h"

namespace Maize
{
    struct SpriteRenderer;
    struct MeshRenderer;

    namespace Internal
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

            /**
             * Handles the removal of the mesh renderer component, removing it from the spatial index.
             * @param entity The entity.
             */
            static void OnMeshRendererRemove(flecs::entity entity, const MeshRenderer&);

            /**
             * Adds the entity to the spatial index when the entity components were deferred.
             * @param entity The entity.
             * @param position The position component.
             * @param meshRenderer The sprite renderer component,
             */
            static void HandleMeshRendererDefer(flecs::entity entity, const Position& position, const MeshRenderer& meshRenderer);
        };
    } // Internal
} // Maize
