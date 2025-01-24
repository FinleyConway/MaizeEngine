#pragma once

#include <Maize.h>

#include "Utils/Rail.h"

// TODO: Separate this component
struct RailSelector
{
    enum class AxisLock { None, X, Y, XY, YX };

    Rail::Type currentType = Rail::Type::None;
    AxisLock lockState = AxisLock::None;
    Maize::Vec2f initialMousePosition;

    std::unordered_map<std::underlying_type_t<Rail::Type>, Maize::IntRect> autoRails;

    // remove these later on
    std::weak_ptr<sf::Texture> texture;
    Maize::Vec2i gridOffset = Maize::Vec2i(0, 32);

    RailSelector() = default;

    RailSelector(const std::shared_ptr<sf::Texture>& texture,
        const std::unordered_map<std::underlying_type_t<Rail::Type>, Maize::IntRect>& autoRails)
        : autoRails(autoRails), texture(texture) {}

    Maize::IntRect GetBitRail(uint8_t type) const
    {
        if (autoRails.contains(type))
        {
            return autoRails.at(type);
        }

        return Maize::IntRect();
    }
};
