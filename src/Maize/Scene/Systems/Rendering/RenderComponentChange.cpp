#include "PrecompiledHeader.h"
#include "Maize/Scene/Systems/Rendering/RenderComponentChange.h"

#include "Maize/Scene/Components/Rendering/DeferredRenderable.h"
#include "Maize/Scene/Components/Rendering/RenderingContext.h"
#include "Maize/Scene/Components/Rendering/SpriteRenderer.h"
#include "Maize/Utils/SpatialHashGrid.h"

namespace Maize::Internal
{
    void RenderComponentChange::OnSpriteRendererRemove(flecs::entity entity, const SpriteRenderer&)
    {
        PROFILE_FUNCTION();

        const auto* ctx = entity.world().get<RenderingContext>();

        CORE_ASSERT(ctx != nullptr, "Rendering context has not been added!")
        CORE_ASSERT(ctx->spatialIndex != nullptr, "Rendering context was created but spatial index wasn't!")

        ctx->spatialIndex->Remove(entity);
    }

    void RenderComponentChange::HandleSpriteRendererDefer(flecs::entity entity, const Position& position,
        const SpriteRenderer& spriteRenderer)
    {
        PROFILE_FUNCTION();

        const auto* ctx = entity.world().get<RenderingContext>();

        CORE_ASSERT(ctx != nullptr, "Rendering context has not been added!")
        CORE_ASSERT(ctx->spatialIndex != nullptr, "Rendering context was created but spatial index wasn't!")

        const auto globalBounds = spriteRenderer.GetGlobalBounds(position);

        ctx->spatialIndex->Insert(entity, globalBounds);

        entity.remove<DeferredRenderable>();
    }
} // Maize