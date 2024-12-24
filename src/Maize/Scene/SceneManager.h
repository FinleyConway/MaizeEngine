#pragma once

#include <SFML/Graphics.hpp>
#include <flecs.h>

#include "Maize/Scene/Scene.h"
#include "Maize/Utils/SpatialHashGrid.h"
#include "Maize/Scene/Systems/InputSystem.h"

namespace Maize::Internal
{
    class Renderer;

    /**
    * Manages the entire game and all the entities within and between the scenes.
    */
    class SceneManager
    {
    public:
        explicit SceneManager(Renderer& renderer);

        ~SceneManager();

        bool LoadScene(std::unique_ptr<Scene> newScene);

        const std::unique_ptr<Scene>& GetActiveScene() const { return m_ActiveScene; }

        void Quit() const;

        void OnEvent(const std::optional<sf::Event>& event) const;
        void OnUpdate(float deltaTime) const;

    private:
        void ChangeSceneObserver();

    private:
        flecs::world m_World;
        std::unique_ptr<Scene> m_ActiveScene = nullptr;

        SpatialHashGrid m_SpatialHashGrid;
        InputSystem m_InputHandler;
    };
} // Maize::Internal
