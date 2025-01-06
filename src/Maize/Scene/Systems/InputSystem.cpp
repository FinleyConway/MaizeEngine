#include "PrecompiledHeader.h"
#include "Maize/Scene/Systems/InputSystem.h"

#include "Maize/Math/Vec2.h"
#include "Maize/Scene/Components/Input.h"

namespace Maize::Internal
{
    InputSystem::InputSystem(const flecs::world& world, const sf::RenderWindow& window): m_World(world), m_Window(window)
    {
        // create an input singleton
        m_World.add<Input>();
    }

    void InputSystem::OnEvent(const std::optional<sf::Event>& event) const
    {
        PROFILE_FUNCTION();

        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            OnKeyPressed(*keyPressed);

        if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>())
            OnKeyReleased(*keyReleased);

        if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>())
            OnMouseMoved(*mouseMoved);

        if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
            OnMouseButtonPressed(*mouseButtonPressed);

        if (const auto* mouseButtonReleased = event->getIf<sf::Event::MouseButtonReleased>())
            OnMouseButtonReleased(*mouseButtonReleased);

        if (const auto* mouseWheelScrolled = event->getIf<sf::Event::MouseWheelScrolled>())
            OnMouseWheelScrolled(*mouseWheelScrolled);
    }

    void InputSystem::OnUpdateEnd() const
    {
        PROFILE_FUNCTION();

        // reset input singleton every frame
        auto& input = m_World.ensure<Input>();
        input.keyDownQuery.reset();
        input.keyUpQuery.reset();
        input.mouseDownQuery.reset();
        input.mouseUpQuery.reset();
        input.scrollWheelDelta = 0.0f;
    }

    void InputSystem::OnKeyPressed(const sf::Event::KeyPressed& event) const
    {
        const auto codeIndex = static_cast<int32_t>(event.code);
        if (codeIndex == -1) return; // invalid/unknown key

        auto& input = m_World.ensure<Input>();

        input.keyDownQuery.set(codeIndex);
        input.keyUpQuery.reset(codeIndex);
    }

    void InputSystem::OnKeyReleased(const sf::Event::KeyReleased& event) const
    {
        const auto codeIndex = static_cast<int32_t>(event.code);
        if (codeIndex == -1) return; // invalid/unknown key

        auto& input = m_World.ensure<Input>();

        input.keyDownQuery.reset(codeIndex);
        input.keyUpQuery.set(codeIndex);
    }

    void InputSystem::OnMouseMoved(const sf::Event::MouseMoved& event) const
    {
        auto& input = m_World.ensure<Input>();
        const auto position = m_Window.mapPixelToCoords(event.position);

        input.mousePosition = Vec2f(position.x, -position.y); // flip y axis so y is up
    }

    void InputSystem::OnMouseButtonPressed(const sf::Event::MouseButtonPressed& event) const
    {
        const auto codeIndex = static_cast<int32_t>(event.button);
        if (codeIndex == -1) return; // invalid/unknown key

        auto& input = m_World.ensure<Input>();

        input.mouseDownQuery.set(codeIndex);
        input.mouseUpQuery.reset(codeIndex);
    }

    void InputSystem::OnMouseButtonReleased(const sf::Event::MouseButtonReleased& event) const
    {
        const auto codeIndex = static_cast<int32_t>(event.button);
        if (codeIndex == -1) return; // invalid/unknown key

        auto& input = m_World.ensure<Input>();

        input.mouseDownQuery.reset(codeIndex);
        input.mouseUpQuery.set(codeIndex);
    }

    void InputSystem::OnMouseWheelScrolled(const sf::Event::MouseWheelScrolled& event) const
    {
        auto& input = m_World.ensure<Input>();

        input.scrollWheelDelta = event.delta;
    }
} // Internal::Maize
