#include "PrecompiledHeader.h"
#include "Maize/Scene/Systems/Rendering/RenderComponentChange.h"

#include "Maize/Scene/Components/Rendering/RenderingContext.h"
#include "Maize/Scene/Components/Rendering/MeshRenderer.h"
#include "Maize/Utils/SpatialHashGrid.h"

namespace Maize::Internal
{
    void RenderComponentChange::OnSpriteRendererRemove(flecs::entity entity, const SpriteRenderer&)
    {
        PROFILE_FUNCTION();

        const auto* ctx = GetRenderingContext(entity);

        ctx->spatialIndex->Remove(entity);
    }

    void RenderComponentChange::HandleSpriteRendererDefer(flecs::entity entity, const SpriteRenderer& spriteRenderer)
    {
        HandleRendererChange(entity, spriteRenderer);
    }

    void RenderComponentChange::OnMeshRendererRemove(flecs::entity entity, const MeshRenderer&)
    {
        PROFILE_FUNCTION();

        const auto* ctx = GetRenderingContext(entity);

        ctx->spatialIndex->Remove(entity);
    }

    void RenderComponentChange::HandleMeshRendererDefer(flecs::entity entity, const MeshRenderer& meshRenderer)
    {
        HandleRendererChange(entity, meshRenderer);
    }

    const RenderingContext* RenderComponentChange::GetRenderingContext(flecs::entity entity)
    {
        const auto* ctx = entity.world().get<RenderingContext>();

        CORE_ASSERT(ctx != nullptr, "Rendering context has not been added!")
        CORE_ASSERT(ctx->spatialIndex != nullptr, "Rendering context was created but spatial index wasn't!")

        return ctx;
    }
} // Maize