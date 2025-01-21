#pragma once

#include <Maize.h>

#include "Utils/Rail.h"

// TODO: Separate this component
struct RailSelector
{
    enum class AxisLock { None, X, Y, XY, YX };

    uint8_t currentBitset = 0;
    Rail::Type currentType = Rail::Type::None;
    AxisLock lockState = AxisLock::None;
    Maize::Vec2f initialMousePosition;

    std::unordered_map<Rail::Type, Maize::IntRect> railType;
    std::unordered_map<uint8_t, Maize::IntRect> autoRails;

    // remove these later on
    std::weak_ptr<sf::Texture> texture;
    Maize::Vec2i gridOffset = Maize::Vec2i(0, 32);

    RailSelector() = default;

    RailSelector(const std::shared_ptr<sf::Texture>& texture, const std::unordered_map<Rail::Type, Maize::IntRect>& railTypes,
        const std::unordered_map<uint8_t, Maize::IntRect>& autoRails)
        : railType(railTypes), autoRails(autoRails), texture(texture) {}

    Maize::IntRect GetAtlas(Rail::Type type) const
    {
        if (railType.contains(type))
        {
            return railType.at(type);
        }

        return Maize::IntRect();
    }

    Maize::IntRect GetBitRail(uint8_t type) const
    {
        if (autoRails.contains(type))
        {
            return autoRails.at(type);
        }

        return GetAtlas(currentType);
    }
};
