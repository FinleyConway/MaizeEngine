#include "PrecompiledHeader.h"
#include "Maize/Scene/Systems/Rendering/RenderingSystem.h"

#include "Maize/Rendering/Renderer.h"
#include "Maize/Scene/Components/Rendering/Camera.h"
#include "Maize/Scene/Components/Rendering/RenderingContext.h"
#include "Maize/Scene/Components/Rendering/SpriteRenderer.h"
#include "Maize/Scene/Components/Rendering/MeshRenderer.h"
#include "Maize/Utils/SpatialHashGrid.h"

namespace Maize::Internal
{
    void RenderingSystem::Render(flecs::entity entity, const Position& position, Camera& camera)
    {
        PROFILE_FUNCTION();

        const auto* ctx = entity.world().get<RenderingContext>();
        CORE_ASSERT(ctx != nullptr, "Rendering context has not been added!");
        CORE_ASSERT(ctx->spatialIndex != nullptr, "Rendering context was created but spatial index wasn't!");
        CORE_ASSERT(ctx->renderer != nullptr, "Rendering context was created but renderer wasn't!");

        // set up the current camera view
        const auto view = SetupCurrentCamera(ctx->renderer, position, camera);
        const auto viewBounds = sf::FloatRect(view.getCenter() - view.getSize() / 2.0f, view.getSize());

        // query and render all visible entities based on the camera's view
        const auto queriedEntities = ctx->spatialIndex->Query({
            viewBounds.position.x, viewBounds.position.y, viewBounds.size.x, viewBounds.size.y,
        });

        RenderEntities(queriedEntities, entity.world(), ctx->renderer);
    }

    void RenderingSystem::RenderEntities(const std::vector<flecs::entity_t>& entities, flecs::world world, Renderer* renderer)
    {
        PROFILE_FUNCTION();

        for (const auto entity : entities)
        {
            auto e = world.entity(entity);
            const auto p = e.ensure<Position>();

            if (const auto* sprite = e.get<SpriteRenderer>())
                RenderSprite(renderer, *sprite, p);

            if (const auto* mesh = e.get<MeshRenderer>())
                RenderMesh(renderer, *mesh, p);

            if (const auto* grid = e.get<GridRenderer>())
                RenderGrid(renderer, *grid, p);
        }
    }

    sf::View RenderingSystem::SetupCurrentCamera(const Renderer* renderer, const Position& position, Camera& camera)
    {
        PROFILE_FUNCTION();

        // create the current view
        const auto windowSize = renderer->GetWindowSize();
        auto view = sf::View({ position.x, -position.y }, sf::Vector2f(windowSize));

        // apply viewport
        const auto viewport = sf::FloatRect(
            { camera.viewport.x, camera.viewport.y },
            { camera.viewport.width, camera.viewport.height }
        );
        view.setViewport(viewport);

        // apply zoom
        const auto viewSize = view.getSize();
        camera.zoom = std::max(camera.zoom, 0.1f);
        view.setSize({ viewSize.x / camera.zoom, viewSize.y / camera.zoom });

        // set the current view for the renderer
        renderer->SetCurrentView(view);

        return view;
    }

    sf::Transform RenderingSystem::CreateTransform(const Position& position, Vec2f pivot)
    {
        PROFILE_FUNCTION();

        sf::Transform transform = sf::Transform::Identity;

        transform.translate({ position.x - pivot.x, -(position.y + pivot.y) });

        return transform;
    }

    sf::RenderStates RenderingSystem::CreateRenderState(const sf::Transform& transform, const std::shared_ptr<sf::Texture>& texture)
    {
        PROFILE_FUNCTION();

        sf::RenderStates state;

        state.transform *= transform;
        state.texture = texture.get();

        return state;
    }

    void RenderingSystem::RenderSprite(Renderer* renderer, const SpriteRenderer& spriteRenderer, const Position& position)
    {
        PROFILE_FUNCTION();

        const auto& sprite = spriteRenderer.sprite;
        const auto pivot = sprite.GetPivot();
        const auto& texture = sprite.GetTexture().lock();
        const auto& vertices = sprite.GetVertices();

        const sf::Transform transform = CreateTransform(position, pivot);
        const sf::RenderStates state = CreateRenderState(transform, texture);

        renderer->Draw(vertices, state);
    }

    void RenderingSystem::RenderMesh(Renderer* renderer, const MeshRenderer& meshRenderer, const Position& position)
    {
        PROFILE_FUNCTION();

        const auto& vertices = meshRenderer.mesh.GetVertices();
        const auto& texture = meshRenderer.texture.lock();

        const sf::Transform transform = CreateTransform(position);
        const sf::RenderStates state = CreateRenderState(transform, texture);

        renderer->Draw(vertices, state);
    }

    void RenderingSystem::RenderGrid(Renderer* renderer, const GridRenderer& gridRenderer, const Position& position)
    {
        PROFILE_FUNCTION();

        const auto& vertices = gridRenderer.mesh.GetVertices();
        const auto& texture = gridRenderer.texture.lock();

        const sf::Transform transform = CreateTransform(position);
        const sf::RenderStates state = CreateRenderState(transform, texture);

        renderer->Draw(vertices, state);
    }
} // Maize::Internal
