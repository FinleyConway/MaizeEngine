#pragma once

#include <flecs.h>

#include "Maize/Scene/Components/Position.h"
#include "Maize/Scene/Components/Rendering/DeferredRenderable.h"
#include "Maize/Scene/Components/Rendering/GridRenderer.h"
#include "Maize/Scene/Components/Rendering/MeshRenderer.h"
#include "Maize/Scene/Components/Rendering/RenderingContext.h"
#include "Maize/Scene/Components/Rendering/SpriteRenderer.h"
#include "Maize/Utils/SpatialHashGrid.h"

namespace Maize::Internal
{
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
         * @param spriteRenderer The sprite renderer component.
         */
        static void HandleSpriteRendererDefer(flecs::entity entity, const SpriteRenderer& spriteRenderer);

        /**
         * Handles the removal of the mesh renderer component, removing it from the spatial index.
         * @param entity The entity.
         */
        static void OnMeshRendererRemove(flecs::entity entity, const MeshRenderer&);

        /**
         * Adds the entity to the spatial index when the entity components were deferred.
         * @param entity The entity.
         * @param meshRenderer The mesh renderer component,
         */
        static void HandleMeshRendererDefer(flecs::entity entity, const MeshRenderer& meshRenderer);

        /**
         * Handles the removal of the grid renderer component, removing it from the spatial index.
         * @param entity The entity.
         */
        static void OnGridRendererRemove(flecs::entity entity, const GridRenderer&);

        /**
         * Adds the entity to the spatial index when the entity components were deferred.
         * @param entity The entity.
         * @param gridRenderer The grid renderer component,
         */
        static void HandleGridRendererDefer(flecs::entity entity, const GridRenderer& gridRenderer);

    private:
        static const RenderingContext* GetRenderingContext(flecs::entity entity);

        template<typename T>
        static void HandleRendererChange(flecs::entity entity, const T& renderer)
        {
            PROFILE_FUNCTION();

            const auto* ctx = GetRenderingContext(entity);
            const auto position = entity.ensure<Position>();
            const auto globalBounds = renderer.GetGlobalBounds({ position.x, position.y }); // a bit unsafe

            ctx->spatialIndex->Relocate(entity, globalBounds);

            entity.remove<DeferredRenderable>();
        }
    };
} // Maize::Internal
