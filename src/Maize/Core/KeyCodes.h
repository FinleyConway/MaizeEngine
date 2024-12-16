#pragma once

#include <SFML/Graphics.hpp>

namespace Maize
{
    enum class KeyCode
    {
        Unknown = sf::Keyboard::Unknown,

        // alphabets
        A = sf::Keyboard::A,
        B = sf::Keyboard::B,
        C = sf::Keyboard::C,
        D = sf::Keyboard::D,
        E = sf::Keyboard::E,
        F = sf::Keyboard::F,
        G = sf::Keyboard::G,
        H = sf::Keyboard::H,
        I = sf::Keyboard::I,
        J = sf::Keyboard::J,
        K = sf::Keyboard::K,
        L = sf::Keyboard::L,
        M = sf::Keyboard::M,
        N = sf::Keyboard::N,
        O = sf::Keyboard::O,
        P = sf::Keyboard::P,
        Q = sf::Keyboard::Q,
        R = sf::Keyboard::R,
        S = sf::Keyboard::S,
        T = sf::Keyboard::T,
        U = sf::Keyboard::U,
        V = sf::Keyboard::V,
        W = sf::Keyboard::W,
        X = sf::Keyboard::X,
        Y = sf::Keyboard::Y,
        Z = sf::Keyboard::Z,

        // numeric keys
        Num0 = sf::Keyboard::Num0,
        Num1 = sf::Keyboard::Num1,
        Num2 = sf::Keyboard::Num2,
        Num3 = sf::Keyboard::Num3,
        Num4 = sf::Keyboard::Num4,
        Num5 = sf::Keyboard::Num5,
        Num6 = sf::Keyboard::Num6,
        Num7 = sf::Keyboard::Num7,
        Num8 = sf::Keyboard::Num8,
        Num9 = sf::Keyboard::Num9,

        // function keys
        F1 = sf::Keyboard::F1,
        F2 = sf::Keyboard::F2,
        F3 = sf::Keyboard::F3,
        F4 = sf::Keyboard::F4,
        F5 = sf::Keyboard::F5,
        F6 = sf::Keyboard::F6,
        F7 = sf::Keyboard::F7,
        F8 = sf::Keyboard::F8,
        F9 = sf::Keyboard::F9,
        F10 = sf::Keyboard::F10,
        F11 = sf::Keyboard::F11,
        F12 = sf::Keyboard::F12,

        // arrow keys
        Up = sf::Keyboard::Up,
        Down = sf::Keyboard::Down,
        Left = sf::Keyboard::Left,
        Right = sf::Keyboard::Right,

        // other keys
        Space = sf::Keyboard::Space,
        Enter = sf::Keyboard::Enter,
        Escape = sf::Keyboard::Escape,
        Tab = sf::Keyboard::Tab,
        Shift = sf::Keyboard::LShift,
        Ctrl = sf::Keyboard::LControl,
        Alt = sf::Keyboard::LAlt,
        Backspace = sf::Keyboard::Backspace,
        Delete = sf::Keyboard::Delete,
        Home = sf::Keyboard::Home,
        End = sf::Keyboard::End,
        PageUp = sf::Keyboard::PageUp,
        PageDown = sf::Keyboard::PageDown,
        Insert = sf::Keyboard::Insert,
        Pause = sf::Keyboard::Pause,
        Menu = sf::Keyboard::Menu,

        LeftBracket = sf::Keyboard::LBracket,
        RightBracket = sf::Keyboard::RBracket,
        Semicolon = sf::Keyboard::Semicolon,
        Comma = sf::Keyboard::Comma,
        Period = sf::Keyboard::Period,
        Apostrophe = sf::Keyboard::Apostrophe,
        Slash = sf::Keyboard::Slash,
        Backslash = sf::Keyboard::Backslash,
        Grave = sf::Keyboard::Grave,
        Equal = sf::Keyboard::Equal,
        Hyphen = sf::Keyboard::Hyphen,

        Count = sf::Keyboard::KeyCount
    };

    enum class MouseCode
    {
        // main buttons
        Left = sf::Mouse::Left,
        Middle = sf::Mouse::Middle,
        Right = sf::Mouse::Right,

        // side buttons
        Alt1 = sf::Mouse::XButton1,
        Alt2 = sf::Mouse::XButton2,

        Count = sf::Mouse::ButtonCount
    };
} // Maize
