#pragma once

#include <algorithm>

#include <flecs.h>

#include "Maize/Core/Macros/Assert.h"
#include "Maize/Core/Macros/Log.h"
#include "Maize/Rendering/Renderer.h"
#include "Maize/Scene/Components/Position.h"
#include "Maize/Scene/Components/Rendering/Camera.h"
#include "Maize/Scene/Components/Rendering/RenderingContext.h"
#include "Maize/Scene/Components/Rendering/SpriteRenderer.h"
#include "Maize/Utils/SpatialHashGrid.h"

namespace Maize
{
    class RenderingSystem
    {
    public:
        static void UpdateSpriteRendererPosition(flecs::entity entity, const Position& position,
            const SpriteRenderer& spriteRenderer)
        {
            const auto* ctx = entity.world().get<Internal::RenderingContext>();

            CORE_ASSERT(ctx != nullptr, "Rendering context has not been added!")
            CORE_ASSERT(ctx->spatialIndex != nullptr, "Rendering context was created but spatial index wasn't!")

            const auto& globalBounds = spriteRenderer.GetGlobalBounds(position);

            ctx->spatialIndex->Relocate(entity, globalBounds);
        }

        static void Render(flecs::entity entity, const Position& position, Camera& camera)
        {
            const auto* ctx = entity.world().get<Internal::RenderingContext>();

            CORE_ASSERT(ctx != nullptr, "Rendering context has not been added!")
            CORE_ASSERT(ctx->spatialIndex != nullptr, "Rendering context was created but spatial index wasn't!")
            CORE_ASSERT(ctx->renderer != nullptr, "Rendering context was created but renderer wasn't!")

            // preform all the rendering for this current camera
            const auto view = SetupCurrentCamera(ctx->renderer, position, camera);
            const auto viewBounds = sf::FloatRect(view.getCenter() - (view.getSize() / 2.0f), view.getSize());

            // query all entities based on the camera's view
            auto queriedEntities = ctx->spatialIndex->Query({
                viewBounds.position.x, viewBounds.position.y, viewBounds.size.x, viewBounds.size.y,
            });

            // render all the entities
            for (const auto et : queriedEntities)
            {
                auto e = entity.world().entity(et);
                const auto p = e.ensure<Position>();

                // render all types depending on what's on the entity
                if (const auto* sprite = e.get<SpriteRenderer>())
                    RenderSprite(ctx->renderer, *sprite, p);
            }

            printf("%d\n", ctx->renderer->GetDrawCalls());
        }

    private:
        static sf::View SetupCurrentCamera(const Renderer* renderer, const Position& position, Camera& camera)
        {
            // set up the current sfml view using camera component
            const auto windowSize = renderer->GetWindowSize();
            auto view = sf::View({ position.x, position.y }, sf::Vector2f(windowSize));

            // apply viewport
            const auto viewport = sf::FloatRect(
                { camera.viewport.x, camera.viewport.y },
                { camera.viewport.width, camera.viewport.height }
            );
            view.setViewport(viewport);

            // handle camera zoom
            // clamp the view to being within an appropriate range
            const auto viewSize = view.getSize();
            camera.zoom = std::max(camera.zoom, 0.1f);
            view.setSize({ viewSize.x / camera.zoom, viewSize.y / camera.zoom });

            // tell the renderer to use this camera for this current rendering pass
            renderer->SetCurrentView(view);

            return view;
        }

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
