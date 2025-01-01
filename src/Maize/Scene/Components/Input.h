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

        bool GetButtonDown(KeyCode key)
        {
            const auto index = static_cast<int32_t>(key);
            const bool state = keyDownQuery.test(index);

            if (state) keyDownQuery.reset(index);

            return state;
        }

        bool GetButtonHeld(KeyCode key)
        {
            const bool stateUp = keyUpQuery.test(static_cast<int32_t>(key));
            const bool stateDown = keyDownQuery.test(static_cast<int32_t>(key));

            return stateDown && !stateUp;
        }

        bool GetButtonUp(KeyCode key)
        {
            const auto index = static_cast<int32_t>(key);
            const bool state = keyUpQuery.test(index);

            if (state) keyUpQuery.reset(index);

            return state;
        }

        bool GetMouseButtonDown(MouseCode key)
        {
            const auto index = static_cast<int32_t>(key);
            const bool state = mouseDownQuery.test(index);

            if (state) mouseDownQuery.reset(index);

            return state;
        }

        bool GetMouseButtonHeld(MouseCode key)
        {
            const bool stateUp = mouseUpQuery.test(static_cast<int32_t>(key));
            const bool stateDown = mouseDownQuery.test(static_cast<int32_t>(key));

            return stateDown && !stateUp;
        }

        bool GetMouseButtonUp(MouseCode key)
        {
            const auto index = static_cast<int32_t>(key);
            const bool state = mouseUpQuery.test(index);

            if (state) mouseUpQuery.reset(index);

            return state;
        }
    };
} // Maize
