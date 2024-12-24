#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

namespace Maize
{
    namespace Internal
    {
        constexpr inline int32_t KEY_COUNT = sf::Keyboard::KeyCount;
        constexpr inline int32_t BUTTON_COUNT = sf::Mouse::ButtonCount;
    } // Internal

    using KeyCode = sf::Keyboard::Key;
    using MouseCode = sf::Mouse::Button;
} // Maize
