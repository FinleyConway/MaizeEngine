#pragma once

#include "Maize/Core/KeyCodes.h"

namespace Maize
{
    struct Input
    {
        std::bitset<Internal::KEY_COUNT> keyDownQuery;
        std::bitset<Internal::KEY_COUNT> keyUpQuery;
        std::bitset<Internal::BUTTON_COUNT> mouseDownQuery;
        std::bitset<Internal::BUTTON_COUNT> mouseUpQuery;

        Vec2f mousePosition;
        float scrollWheelDelta = 0.0f;

        bool GetButtonDown(KeyCode key) const
        {
            const auto index = static_cast<int32_t>(key);
            const bool state = keyDownQuery.test(index);

            return state;
        }

        bool GetButtonHeld(KeyCode key) const
        {
            const bool stateUp = keyUpQuery.test(static_cast<int32_t>(key));
            const bool stateDown = keyDownQuery.test(static_cast<int32_t>(key));

            return stateDown && !stateUp;
        }

        bool GetButtonUp(KeyCode key) const
        {
            const auto index = static_cast<int32_t>(key);
            const bool state = keyUpQuery.test(index);

            return state;
        }

        bool GetMouseButtonDown(MouseCode key) const
        {
            const auto index = static_cast<int32_t>(key);
            const bool state = mouseDownQuery.test(index);

            return state;
        }

        bool GetMouseButtonHeld(MouseCode key) const
        {
            const bool stateUp = mouseUpQuery.test(static_cast<int32_t>(key));
            const bool stateDown = mouseDownQuery.test(static_cast<int32_t>(key));

            return stateDown && !stateUp;
        }

        bool GetMouseButtonUp(MouseCode key) const
        {
            const auto index = static_cast<int32_t>(key);
            const bool state = mouseUpQuery.test(index);

            return state;
        }
    };
} // Maize
