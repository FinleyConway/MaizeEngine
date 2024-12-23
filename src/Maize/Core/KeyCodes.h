#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

namespace Maize
{
    namespace Internal
    {
        template<typename T>
        constexpr int toInt(T button) { return static_cast<int>(button); }
    } // Internal

    enum class KeyCode
    {
        A = Internal::toInt(sf::Keyboard::Key::A),
        B = Internal::toInt(sf::Keyboard::Key::B),
        C = Internal::toInt(sf::Keyboard::Key::C),
        D = Internal::toInt(sf::Keyboard::Key::D),
        E = Internal::toInt(sf::Keyboard::Key::E),
        F = Internal::toInt(sf::Keyboard::Key::F),
        G = Internal::toInt(sf::Keyboard::Key::G),
        H = Internal::toInt(sf::Keyboard::Key::H),
        I = Internal::toInt(sf::Keyboard::Key::I),
        J = Internal::toInt(sf::Keyboard::Key::J),
        K = Internal::toInt(sf::Keyboard::Key::K),
        L = Internal::toInt(sf::Keyboard::Key::L),
        M = Internal::toInt(sf::Keyboard::Key::M),
        N = Internal::toInt(sf::Keyboard::Key::N),
        O = Internal::toInt(sf::Keyboard::Key::O),
        P = Internal::toInt(sf::Keyboard::Key::P),
        Q = Internal::toInt(sf::Keyboard::Key::Q),
        R = Internal::toInt(sf::Keyboard::Key::R),
        S = Internal::toInt(sf::Keyboard::Key::S),
        T = Internal::toInt(sf::Keyboard::Key::T),
        U = Internal::toInt(sf::Keyboard::Key::U),
        V = Internal::toInt(sf::Keyboard::Key::V),
        W = Internal::toInt(sf::Keyboard::Key::W),
        X = Internal::toInt(sf::Keyboard::Key::X),
        Y = Internal::toInt(sf::Keyboard::Key::Y),
        Z = Internal::toInt(sf::Keyboard::Key::Z),

        Num0 = Internal::toInt(sf::Keyboard::Key::Num0),
        Num1 = Internal::toInt(sf::Keyboard::Key::Num1),
        Num2 = Internal::toInt(sf::Keyboard::Key::Num2),
        Num3 = Internal::toInt(sf::Keyboard::Key::Num3),
        Num4 = Internal::toInt(sf::Keyboard::Key::Num4),
        Num5 = Internal::toInt(sf::Keyboard::Key::Num5),
        Num6 = Internal::toInt(sf::Keyboard::Key::Num6),
        Num7 = Internal::toInt(sf::Keyboard::Key::Num7),
        Num8 = Internal::toInt(sf::Keyboard::Key::Num8),
        Num9 = Internal::toInt(sf::Keyboard::Key::Num9),

        F1  = Internal::toInt(sf::Keyboard::Key::F1),
        F2  = Internal::toInt(sf::Keyboard::Key::F2),
        F3  = Internal::toInt(sf::Keyboard::Key::F3),
        F4  = Internal::toInt(sf::Keyboard::Key::F4),
        F5  = Internal::toInt(sf::Keyboard::Key::F5),
        F6  = Internal::toInt(sf::Keyboard::Key::F6),
        F7  = Internal::toInt(sf::Keyboard::Key::F7),
        F8  = Internal::toInt(sf::Keyboard::Key::F8),
        F9  = Internal::toInt(sf::Keyboard::Key::F9),
        F10 = Internal::toInt(sf::Keyboard::Key::F10),
        F11 = Internal::toInt(sf::Keyboard::Key::F11),
        F12 = Internal::toInt(sf::Keyboard::Key::F12),

        Up          = Internal::toInt(sf::Keyboard::Key::Up),
        Down        = Internal::toInt(sf::Keyboard::Key::Down),
        Left        = Internal::toInt(sf::Keyboard::Key::Left),
        Right       = Internal::toInt(sf::Keyboard::Key::Right),

        Space       = Internal::toInt(sf::Keyboard::Key::Space),
        Enter       = Internal::toInt(sf::Keyboard::Key::Enter),
        Escape      = Internal::toInt(sf::Keyboard::Key::Escape),
        Tab         = Internal::toInt(sf::Keyboard::Key::Tab),
        Shift       = Internal::toInt(sf::Keyboard::Key::LShift),
        Ctrl        = Internal::toInt(sf::Keyboard::Key::LControl),
        Alt         = Internal::toInt(sf::Keyboard::Key::LAlt),
        Backspace   = Internal::toInt(sf::Keyboard::Key::Backspace),
        Delete      = Internal::toInt(sf::Keyboard::Key::Delete),
        Home        = Internal::toInt(sf::Keyboard::Key::Home),
        End         = Internal::toInt(sf::Keyboard::Key::End),
        PageUp      = Internal::toInt(sf::Keyboard::Key::PageUp),
        PageDown    = Internal::toInt(sf::Keyboard::Key::PageDown),
        Insert      = Internal::toInt(sf::Keyboard::Key::Insert),
        Pause       = Internal::toInt(sf::Keyboard::Key::Pause),
        Menu        = Internal::toInt(sf::Keyboard::Key::Menu),

        LeftBracket     = Internal::toInt(sf::Keyboard::Key::LBracket),
        RightBracket    = Internal::toInt(sf::Keyboard::Key::RBracket),
        Semicolon       = Internal::toInt(sf::Keyboard::Key::Semicolon),
        Comma           = Internal::toInt(sf::Keyboard::Key::Comma),
        Period          = Internal::toInt(sf::Keyboard::Key::Period),
        Apostrophe      = Internal::toInt(sf::Keyboard::Key::Apostrophe),
        Slash           = Internal::toInt(sf::Keyboard::Key::Slash),
        Backslash       = Internal::toInt(sf::Keyboard::Key::Backslash),
        Grave           = Internal::toInt(sf::Keyboard::Key::Grave),
        Equal           = Internal::toInt(sf::Keyboard::Key::Equal),
        Hyphen          = Internal::toInt(sf::Keyboard::Key::Hyphen),
    };

    enum class MouseCode
    {
        Left    = Internal::toInt(sf::Mouse::Button::Left),
        Middle  = Internal::toInt(sf::Mouse::Button::Middle),
        Right   = Internal::toInt(sf::Mouse::Button::Right),

        Alt1    = Internal::toInt(sf::Mouse::Button::Extra1),
        Alt2    = Internal::toInt(sf::Mouse::Button::Extra2),
    };
} // Maize
