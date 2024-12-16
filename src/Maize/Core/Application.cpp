#include "Maize/Core/Application.h"

#include "Maize/Core/Macros/Log.h"

namespace Maize
{
    Application::Application(std::string_view title, uint32_t width, uint32_t height) :
        m_Title(title),
        m_Window(sf::VideoMode(width, height), m_Title),
        m_Renderer(m_Window),
        m_SceneManager(m_Window, m_Renderer)
    {
        Log::Initialise();

        m_Window.setKeyRepeatEnabled(false); // disable text editor hold key like functionality
        m_Window.setVerticalSyncEnabled(true); // turn on v-sync by default
    }

    void Application::Quit()
    {
        m_Window.close();
    }

    bool Application::Run()
    {
        sf::Clock clock;

        while (m_Window.isOpen())
        {
            OnEvent();

            const float deltaTime = clock.restart().asSeconds();

            m_Renderer.BeginDrawing();

            m_SceneManager.OnUpdate(deltaTime);

            m_Renderer.EndDrawing();
        }

        return true;
    }

    bool Application::LoadScene(std::unique_ptr<Scene> scene)
    {
        return m_SceneManager.LoadScene(std::move(scene));
    }

    void Application::OnEvent()
    {
        auto event = sf::Event();

        while (m_Window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                m_Window.close();
                m_SceneManager.Quit();
            }
        }
    }
} // Maize
