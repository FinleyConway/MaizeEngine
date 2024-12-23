#pragma once

#include <SFML/Graphics.hpp>

#include "Maize/Rendering/Renderer.h"
#include "Maize/Scene/SceneManager.h"

namespace Maize
{
    class Application
    {
    public:
        Application(std::string_view title, uint32_t width, uint32_t height);

        virtual ~Application() = default;

        bool Run();

        bool LoadScene(std::unique_ptr<Scene> scene);

        void Quit();

    private:
        void OnEvent();

    private:
        std::string m_Title = "MaizeEngine";
        sf::RenderWindow m_Window;
        Internal::Renderer m_Renderer;
        Internal::SceneManager m_SceneManager;
    };
} // Maize
