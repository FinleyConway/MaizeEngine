#include "Maize/Scene/SceneManager.h"

#include "Maize/Core/Macros/Log.h"
#include "Maize/Scene/Components/Rendering/RenderingContext.h"
#include "Maize/Scene/Components/Rendering/SpriteRenderer.h"
#include "Maize/Scene/Systems/Rendering/RenderingSystem.h"

namespace Maize
{
    SceneManager::SceneManager(sf::RenderWindow& window, Renderer& renderer)
    {
        ChangeSceneObserver(); // add scene changer observer to world.

        m_World.set(Internal::RenderingContext(&renderer));
        m_World.system<Position, SpriteRenderer>("RenderingSystem")
            .kind(flecs::OnStore).each(RenderingSystem::Render);

#if ENABLE_FLECS_EXPLORER
		m_World.set<flecs::Rest>({});
		m_World.import<flecs::stats>();
		LOG_CORE_INFO("https://www.flecs.dev/explorer/");
#endif
    }

    SceneManager::~SceneManager()
    {
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

    void SceneManager::OnUpdate(float deltaTime) const
    {
        m_World.progress(deltaTime);
    }

    void SceneManager::ChangeSceneObserver()
    {
        m_World.observer<ChangeScene>("OnChangeScene").event(flecs::OnSet).each(
            [&](flecs::entity e, ChangeScene& sceneChanger)
        {
            LoadScene(std::move(sceneChanger.newScene));
            e.remove<ChangeScene>();
        });
    }
} // Maize
