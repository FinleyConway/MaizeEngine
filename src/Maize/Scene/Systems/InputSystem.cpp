#include "PrecompiledHeader.h"
#include "Maize/Scene/Systems/InputSystem.h"

#include "Maize/Scene/Components/Input.h"

namespace Maize::Internal
{
    InputSystem::InputSystem(flecs::world& world): m_World(world)
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

        /*if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>())
                OnMouseMoved(*mouseMoved);*/

        if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
            OnMouseButtonPressed(*mouseButtonPressed);

        if (const auto* mouseButtonReleased = event->getIf<sf::Event::MouseButtonReleased>())
            OnMouseButtonReleased(*mouseButtonReleased);
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
} // Internal::Maize
