#include "PrecompiledHeader.h"
#include "Maize/Scene/SceneManager.h"

#include "Maize/Rendering/Renderer.h"
#include "Maize/Scene/Components/ChangeScene.h"
#include "Maize/Scene/Components/Rendering/DeferredRenderable.h"
#include "Maize/Scene/Components/Rendering/RenderingContext.h"
#include "Maize/Scene/Components/Rendering/SpriteRenderer.h"
#include "Maize/Scene/Components/Rendering/MeshRenderer.h"
#include "Maize/Scene/Components/Rendering/GridRenderer.h"
#include "Maize/Scene/Components/Rendering/Camera.h"
#include "Maize/Scene/Systems/Rendering/RenderComponentChange.h"
#include "Maize/Scene/Systems/Rendering/RenderingSystem.h"
#include "Maize/Utils/SpatialHashGrid.h"

namespace Maize::Internal
{
    SceneManager::SceneManager(Renderer& renderer) :
        m_SpatialHashGrid(1024), m_InputHandler(m_World, renderer.GetWindow())
    {
        PROFILE_FUNCTION();

        ChangeSceneObserver(); // add scene changer observer to world.

        m_World.set(RenderingContext(&renderer, &m_SpatialHashGrid));

        m_World.observer<Position>()
            .event(flecs::OnSet)
            .each([](flecs::entity entity, Position&) {
                entity.add<DeferredRenderable>();
            });

        // on add/set sprite renderer
        m_World.observer<SpriteRenderer>()
            .event(flecs::OnAdd)
            .each([](flecs::entity entity, SpriteRenderer&) {
                entity.add<DeferredRenderable>();
        });
        m_World.observer<SpriteRenderer>().event(flecs::OnSet)
            .each([](flecs::entity entity, SpriteRenderer&)
            {
                entity.add<DeferredRenderable>();
            });

        // on add/set mesh renderer
        m_World.observer<MeshRenderer>()
            .event(flecs::OnAdd)
            .each([](flecs::entity entity, MeshRenderer&)
            {
                entity.add<DeferredRenderable>();
            });
        m_World.observer<MeshRenderer>().event(flecs::OnSet)
            .each([](flecs::entity entity, MeshRenderer&)
            {
                entity.add<DeferredRenderable>();
            });

        // on add/set mesh renderer
        m_World.observer<GridRenderer>()
            .event(flecs::OnAdd)
            .each([](flecs::entity entity, GridRenderer&)
            {
                entity.add<DeferredRenderable>();
            });
        m_World.observer<GridRenderer>().event(flecs::OnSet)
            .each([](flecs::entity entity, GridRenderer&)
            {
                entity.add<DeferredRenderable>();
            });


        m_World.observer<const SpriteRenderer>("OnSpriteRendererRemove")
            .event(flecs::OnRemove)
            .each(RenderComponentChange::OnSpriteRendererRemove);
        m_World.observer<const MeshRenderer>("OnMeshRendererRemove")
            .event(flecs::OnRemove)
            .each(RenderComponentChange::OnMeshRendererRemove);
        m_World.observer<const GridRenderer>("OnGridRendererRemove")
             .event(flecs::OnRemove)
             .each(RenderComponentChange::OnGridRendererRemove);

        m_World.system<const SpriteRenderer>("HandleSpriteRendererDefer")
            .with<DeferredRenderable>() // only triggers when having this component
            .immediate().kind(flecs::PreStore)
            .each(RenderComponentChange::HandleSpriteRendererDefer);
        m_World.system<const MeshRenderer>("HandleMeshRendererDefer")
            .with<DeferredRenderable>() // only triggers when having this component
            .immediate().kind(flecs::PreStore)
            .each(RenderComponentChange::HandleMeshRendererDefer);
        m_World.system<const GridRenderer>("HandleGridRendererDefer")
            .with<DeferredRenderable>() // only triggers when having this component
            .immediate().kind(flecs::PreStore)
            .each(RenderComponentChange::HandleGridRendererDefer);

        m_World.system<const Position, Camera>("RenderingSystem")
            .kind(flecs::OnStore)
            .each(RenderingSystem::Render);

#if ENABLE_FLECS_EXPLORER
		m_World.set<flecs::Rest>({});
		m_World.import<flecs::stats>();
		LOG_CORE_INFO("https://www.flecs.dev/explorer/");
#endif
    }

    SceneManager::~SceneManager()
    {
        PROFILE_FUNCTION();

        // shutdown any active scenes
        if (m_ActiveScene)
        {
            m_ActiveScene->Shutdown();
            m_ActiveScene.reset();
        }

        // wait until flecs is finished before destroying the world
        while (!m_World.should_quit())
        {
            m_World.progress();
        }
    }

    bool SceneManager::LoadScene(std::unique_ptr<Scene> newScene)
    {
        PROFILE_FUNCTION();

        if (newScene != nullptr)
        {
            if (m_ActiveScene != nullptr)
            {
                m_ActiveScene->Shutdown();
            }

            m_ActiveScene = std::move(newScene);
            m_ActiveScene->Initialise(m_World);

            return true;
        }

        CORE_LOG_WARN("Fail to load scene: {}", typeid(newScene).name());

        return false;
    }

    void SceneManager::Quit() const
    {
        m_World.quit();
    }

    void SceneManager::OnEvent(const std::optional<sf::Event>& event) const
    {
        m_InputHandler.OnEvent(event);
    }

    void SceneManager::OnUpdate(float deltaTime) const
    {
        PROFILE_FUNCTION();

        m_World.progress(deltaTime);
        m_InputHandler.OnUpdateEnd();
    }

    void SceneManager::ChangeSceneObserver()
    {
        m_World.observer<ChangeScene>("OnChangeScene").event(flecs::OnSet).each(
            [&](flecs::entity e, ChangeScene& sceneChanger)
        {
            PROFILE_FUNCTION();

            LoadScene(std::move(sceneChanger.newScene));
            e.remove<ChangeScene>();
        });
    }
} // Maize
