#include "PrecompiledHeader.h"
#include "Maize/Core/Application.h"

namespace Maize
{
    Application::Application(std::string_view title, uint32_t width, uint32_t height) :
        m_Title(title),
        m_Window(sf::VideoMode({ width, height }), m_Title),
        m_Renderer(m_Window),
        m_SceneManager(m_Renderer)
    {
        Log::Initialise();

        PROFILE_BEGIN_SESSION("Maize", "Maize-Benchmark.json", 512);

        m_Window.setKeyRepeatEnabled(false); // disable text editor hold key like functionality
    }

    Application::~Application()
    {
        PROFILE_END_SESSION();
    }

    void Application::Quit()
    {
        m_Window.close();
    }

    bool Application::Run()
    {
        //PROFILE_FUNCTION();

        sf::Clock clock;

        while (m_Window.isOpen())
        {
            PROFILE_SCOPE("Run Loop");

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
        while (const std::optional event = m_Window.pollEvent())
        {
            m_SceneManager.OnEvent(event);

            if (event->is<sf::Event::Closed>())
            {
                m_Window.close();
                m_SceneManager.Quit();
            }
        }
    }
} // Maize
