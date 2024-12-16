#pragma once

#include <SFML/Graphics.hpp>
#include <flecs.h>

#include <memory>

#include "Maize/Rendering/Renderer.h"
#include "Maize/Scene/Scene.h"

namespace Maize
{
    /**
     * Manages the entire game and all the entities within and between the scenes.
     */
    class SceneManager
    {
    public:
        SceneManager(sf::RenderWindow& window, Renderer& renderer);

        ~SceneManager();

        bool LoadScene(std::unique_ptr<Scene> newScene);

        const std::unique_ptr<Scene>& GetActiveScene() const { return m_ActiveScene; }

        void ForceQuit() const;

        void OnEvent(sf::Event& event);

        void OnUpdate(float deltaTime);

    private:
        void ChangeSceneObserver();

    private:
        flecs::world m_World;
        std::unique_ptr<Scene> m_ActiveScene = nullptr;
    };
} // Maize
